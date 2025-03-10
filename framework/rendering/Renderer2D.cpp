#include "rendering/Renderer2D.hpp"
#include "math/suisho_math.hpp"
#include <cstdlib>
#include <cstring> // memcpy, memset
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "rendering/stb_image.h" // FIXME

using namespace suisho;

static std::vector<char> readBinary(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

Renderer2D::Renderer2D() : frames_(), current_frame_(0), drawed_count_(0) {

}

Renderer2D::~Renderer2D() {

}

bool Renderer2D::initialize() {
    bool ok = device_.initialize();
    if (!ok) {
        return false;
    }
    dynamic_alignment_ = device_.getProperties().limits.minUniformBufferOffsetAlignment;
    if (dynamic_alignment_ > 0) {
        dynamic_alignment_ = (sizeof(ObjectUniformBuffer) + dynamic_alignment_ - 1) & ~(dynamic_alignment_ - 1);
    }

    global_layout_ = device_.createBindingLayout({ {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER } });
    material_layout_ = device_.createBindingLayout({ {0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER} });
    object_layout_ = device_.createBindingLayout({ {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC} });

    // Build default material
    {
        constexpr uint32_t tex_w = 4;
        constexpr uint32_t tex_h = 4;
        constexpr size_t tex_size = tex_w * tex_h * 4; // RGBA
        unsigned char texels[tex_size];
        std::memset(texels, 0xff, tex_size);
        default_material_.texture = device_.createTexture(tex_w, tex_h, texels, VK_FORMAT_R8G8B8A8_SRGB);
        default_material_.binding_set = device_.createBindingSet(material_layout_, {{ 0, default_material_.texture }});
    }

    render_pass_ = device_.createRenderPass();
    VkShaderModule vert = device_.createShaderModule(readBinary(SUISHO_BUILTIN_ASSETS_DIR"/shaders/quad.vert.spv"));
    VkShaderModule frag = device_.createShaderModule(readBinary(SUISHO_BUILTIN_ASSETS_DIR"/shaders/quad.frag.spv"));
    pipeline_ = device_.createGraphicsPipeline(
        vert, frag,
        VertexFormat::kNone,
        { global_layout_.layout, material_layout_.layout, object_layout_.layout },
        render_pass_, pipeline_layout_
    );
    device_.destroyShaderModule(vert);
    device_.destroyShaderModule(frag);

    const auto& swapchain_images = device_.getSwapchainImages();
    createDepthBuffer(swapchain_images[0].extent.width, swapchain_images[0].extent.height);
    createFramebuffers(swapchain_images);
    for (auto& frame : frames_) {
        frame.cmd_execution = device_.createFence(true);
        frame.cmd_buf = device_.createCommandBuffer();
        frame.global_uniform = device_.createBuffer(sizeof(GlobalUniformBuffer), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        frame.object_uniform = device_.createBuffer(dynamic_alignment_ * kMaxObjectsCount, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

#ifdef _MSC_VER
        frame.object_uniform_data = _aligned_malloc(frame.object_uniform.size, dynamic_alignment_);
#else
        frame.object_uniform_data = std::aligned_alloc(dynamic_alignment_, frame.object_uniform.size);
#endif
        if (frame.object_uniform_data == nullptr) {
            throw std::bad_alloc();
        }

        frame.global_binding = device_.createBindingSet(global_layout_, { { 0, frame.global_uniform } });

        const size_t actual_size = frame.object_uniform.size;
        frame.object_uniform.size = dynamic_alignment_; // Binded size
        frame.object_binding = device_.createBindingSet(object_layout_, { { 0, frame.object_uniform } });
        frame.object_uniform.size = actual_size;
    }

    device_.subscribeWindowResize([this](uint32_t w, uint32_t h) {
        if (w == 0 || h == 0) {
            return;
        }

        device_.destroyImage(depth_buffer_);
        for (auto& fb : framebuffers_) {
            device_.destroyFramebuffer(fb);
        }

        createDepthBuffer(w, h);
        createFramebuffers(device_.getSwapchainImages());
    });

    return true;
}

void Renderer2D::createDepthBuffer(uint32_t width, uint32_t height) {
    const VkFormat depth_format = device_.findSupportedFormat(
        { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
    );
    depth_buffer_ = device_.createImage(
        width, height, nullptr,
        depth_format, VK_IMAGE_LAYOUT_UNDEFINED,
        VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        VK_IMAGE_ASPECT_DEPTH_BIT
    );
}

void Renderer2D::createFramebuffers(const std::vector<backend::VulkanImage>& swapchain_images) {
    framebuffers_.resize(swapchain_images.size());
    for (size_t i = 0; i < swapchain_images.size(); ++i) {
        const auto attachments = { swapchain_images[i], depth_buffer_ };
        framebuffers_[i] = device_.createFramebuffer(attachments, render_pass_);
    }
}

void Renderer2D::terminate() {
    device_.waitIdle();

    device_.destroyBindingLayout(object_layout_);
    device_.destroyBindingLayout(material_layout_);
    device_.destroyBindingLayout(global_layout_);
    destroyMaterial(default_material_);

    for (auto& fb : framebuffers_) {
        device_.destroyFramebuffer(fb);
    }

    for (auto& frame : frames_) {
        device_.destroyFence(frame.cmd_execution);
        device_.destroyCommandBuffer(frame.cmd_buf);
        device_.destroyBuffer(frame.global_uniform);
        device_.destroyBuffer(frame.object_uniform);
#ifdef _MSC_VER
        _aligned_free(frame.object_uniform_data);
#else
        std::free(frame.object_uniform_data);
#endif
    }

    device_.destroyImage(depth_buffer_);
    device_.destroyPipeline(pipeline_, pipeline_layout_);
    device_.destroyRenderPass(render_pass_);

    device_.terminate();
}

bool Renderer2D::shouldWindowClose() const {
    return device_.isWindowClosed();
}

bool Renderer2D::beginFrame() {
    if (device_.isWindowMinimized()) {
        return false;
    }

    auto& frame = frames_[current_frame_];
    device_.waitForFence(frame.cmd_execution, UINT64_MAX);
    device_.resetFence(frame.cmd_execution);

    // TODO: Error validation
    if (device_.swapBackBuffer() == UINT32_MAX) {
        return false;
    }

    backend::VulkanCommandBuffer& cmd = frame.cmd_buf;
    cmd.reset();

    cmd.beginRecording();

    const VkExtent2D swapchain_extent = device_.getSwapchainImages()[0].extent;
    std::vector<VkClearValue> clear_values(2);
    clear_values[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
    clear_values[1].depthStencil = { 1.0f, 0 };
    cmd.beginRenderPass(
        render_pass_, framebuffers_[device_.getNextImageIndex()],
        clear_values, swapchain_extent
    );

    cmd.bindGraphicsPipeline(pipeline_);

    VkViewport viewport{};
    viewport.x = viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapchain_extent.width);
    viewport.height = static_cast<float>(swapchain_extent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    cmd.setViewport(viewport);

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = swapchain_extent;
    cmd.setScissor(scissor);

    // Prepare global binding
    GlobalUniformBuffer camera{};
    camera.view = Mat4::lookAt(Vec3(0.0f, 0.0f, -3.0f), Vec3::kZero, -Vec3::kUp);
    camera.proj = Mat4::perspective(45.0f, swapchain_extent.width / static_cast<float>(swapchain_extent.height), 0.1f, 10.0f);
    camera.proj[1][1] *= -1;
    std::memcpy(frame.global_uniform.mapped, &camera, sizeof(GlobalUniformBuffer));
    cmd.bindBindingSet(0, frames_[current_frame_].global_binding, pipeline_layout_); // Global binding is set = 0

    // Bind default material(set = 1)
    cmd.bindBindingSet(1, default_material_.binding_set, pipeline_layout_);
    return true;
}

void Renderer2D::endFrame() {
    auto& frame = frames_[current_frame_];
    std::memcpy(frame.object_uniform.mapped, frame.object_uniform_data, dynamic_alignment_ * drawed_count_);
    device_.flushBuffer(frame.object_uniform, 0, dynamic_alignment_ * drawed_count_);

    backend::VulkanCommandBuffer& cmd = frame.cmd_buf;
    cmd.endRenderPass();

    cmd.endRecording();
    device_.submit(cmd, frame.cmd_execution);
    device_.present();

    current_frame_ = (current_frame_ + 1) % kMaxFramesOverlapped;
    bound_material_ = nullptr;
    drawed_count_ = 0;
}

void Renderer2D::bindMaterial(const Material& material) {
    // Material binding is set = 1
    frames_[current_frame_].cmd_buf.bindBindingSet(1, material.binding_set, pipeline_layout_);
    bound_material_ = &material;
}

void Renderer2D::draw(const Mat4& xform) {
    auto& frame = frames_[current_frame_];
    ObjectUniformBuffer& dst = *reinterpret_cast<ObjectUniformBuffer*>(
        reinterpret_cast<uintptr_t>(frame.object_uniform_data) + (dynamic_alignment_ * drawed_count_)
    );
    dst.model_to_world = xform;

    frame.cmd_buf.bindBindingSetDynamic(2, dynamic_alignment_ * drawed_count_, frame.object_binding, pipeline_layout_);
    frame.cmd_buf.draw(4);
    ++drawed_count_;
}

Material Renderer2D::createMaterial(const std::string& texture_path) {
    int width, height, channels;
    stbi_uc* pixels = stbi_load(texture_path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if (pixels == nullptr) {
        throw std::runtime_error("failed to load " + texture_path);
    }

    Material material{};
    material.texture = device_.createTexture(static_cast<uint32_t>(width), static_cast<uint32_t>(height), pixels, VK_FORMAT_R8G8B8A8_SRGB);
    material.binding_set = device_.createBindingSet(material_layout_, { { 0, material.texture } });

    stbi_image_free(pixels);
    return material;
}

void Renderer2D::destroyMaterial(Material& mat) {
    device_.waitIdle(); // FIXME
    device_.destroyTexture(mat.texture);
    device_.destroyBindingSet(mat.binding_set);
}
