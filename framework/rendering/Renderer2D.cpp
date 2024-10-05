#include "rendering/Renderer2D.h"

using namespace suisho;

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

    const auto& swapchain_images = device_.getSwapchainImages();
    const VkFormat depth_format = device_.findSupportedFormat(
        { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
    );
    depth_buffer_ = device_.createImage(
        swapchain_images[0].extent.width, swapchain_images[0].extent.height, nullptr,
        depth_format, VK_IMAGE_TILING_OPTIMAL,
        VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        VK_IMAGE_ASPECT_DEPTH_BIT
    );

    for (size_t i = 0; i < kMaxFramesOverlapped; ++i) {
        frames_[i].cmd_execution = device_.createFence(true);
        frames_[i].cmd_buf = device_.createCommandBuffer();

        const auto attachments = { swapchain_images[i], depth_buffer_ };
        frames_[i].framebuffer = device_.createFramebuffer(attachments, render_pass_);
    }

    return true;
}

void Renderer2D::terminate() {
    for (size_t i = 0; i < kMaxFramesOverlapped; ++i) {
        device_.destroyFence(frames_[i].cmd_execution);
        device_.destroyCommandBuffer(frames_[i].cmd_buf);
        device_.destroyFramebuffer(frames_[i].framebuffer);
    }

    device_.destroyImage(depth_buffer_);
    device_.destroyRenderPass(render_pass_);

    device_.terminate();
}

bool Renderer2D::shouldWindowClose() const {
    return device_.isWindowClosed();
}

bool Renderer2D::beginFrame() {
    device_.waitForFence(frames_[current_frame_].cmd_execution, UINT64_MAX);
    device_.resetFence(frames_[current_frame_].cmd_execution);

    // vkAcquireNextImageKHR

    backend::VulkanCommandBuffer& cmd = frames_[current_frame_].cmd_buf;
    cmd.reset();

    return true;
}

void Renderer2D::endFrame() {

}
