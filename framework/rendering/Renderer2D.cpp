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

    for (size_t i = 0; i < kMaxFramesOverlapped; ++i) {
        frames_[i].cmd_execution = device_.createFence(true);
        frames_[i].cmd_buf = device_.createCommandBuffer();
    }
}

void Renderer2D::terminate() {
    for (size_t i = 0; i < kMaxFramesOverlapped; ++i) {
        device_.destroyFence(frames_[i].cmd_execution);
        device_.destroyCommandBuffer(frames_[i].cmd_buf);
    }

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
