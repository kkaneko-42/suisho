#include "rendering/Renderer2D.h"
#include <fstream>

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

Renderer2D::Renderer2D() : frames_(), current_frame_(0) {

}

Renderer2D::~Renderer2D() {

}

bool Renderer2D::initialize() {
    bool ok = device_.initialize();
    if (!ok) {
        return false;
    }

    render_pass_ = device_.createRenderPass();
    VkShaderModule vert = device_.createShaderModule(readBinary(SUISHO_BUILTIN_ASSETS_DIR"/shaders/triangle.vert.spv"));
    VkShaderModule frag = device_.createShaderModule(readBinary(SUISHO_BUILTIN_ASSETS_DIR"/shaders/triangle.frag.spv"));
    pipeline_ = device_.createGraphicsPipeline(vert, frag, render_pass_, pipeline_layout_);
    device_.destroyShaderModule(vert);
    device_.destroyShaderModule(frag);

    const auto& swapchain_images = device_.getSwapchainImages();
    createDepthBuffer(swapchain_images[0].extent.width, swapchain_images[0].extent.height);
    createFramebuffers(swapchain_images);
    for (size_t i = 0; i < kMaxFramesOverlapped; ++i) {
        frames_[i].cmd_execution = device_.createFence(true);
        frames_[i].cmd_buf = device_.createCommandBuffer();
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
        depth_format, VK_IMAGE_TILING_OPTIMAL,
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

    for (auto& fb : framebuffers_) {
        device_.destroyFramebuffer(fb);
    }

    for (size_t i = 0; i < kMaxFramesOverlapped; ++i) {
        device_.destroyFence(frames_[i].cmd_execution);
        device_.destroyCommandBuffer(frames_[i].cmd_buf);
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

    device_.waitForFence(frames_[current_frame_].cmd_execution, UINT64_MAX);
    device_.resetFence(frames_[current_frame_].cmd_execution);

    // TODO: Error validation
    next_image_index_ = device_.acquireNextImage();;

    backend::VulkanCommandBuffer& cmd = frames_[current_frame_].cmd_buf;
    cmd.reset();

    cmd.beginRecording();

    const VkExtent2D swapchain_extent = device_.getSwapchainImages()[0].extent;
    std::vector<VkClearValue> clear_values(2);
    clear_values[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
    clear_values[1].depthStencil = { 1.0f, 0 };
    cmd.beginRenderPass(
        render_pass_, framebuffers_[next_image_index_],
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

    cmd.draw(3);

    return true;
}

void Renderer2D::endFrame() {
    backend::VulkanCommandBuffer& cmd = frames_[current_frame_].cmd_buf;
    cmd.endRenderPass();

    cmd.endRecording();
    device_.submit(cmd, frames_[current_frame_].cmd_execution);
    device_.present(next_image_index_);

    current_frame_ = (current_frame_ + 1) % kMaxFramesOverlapped;
}
