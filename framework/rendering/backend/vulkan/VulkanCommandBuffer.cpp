#include "rendering/backend/vulkan/VulkanCommandBuffer.h"

using namespace suisho::backend;

VulkanCommandBuffer::VulkanCommandBuffer(uint32_t& img_idx, VkCommandBuffer cb)
: img_idx_(img_idx), cb_(cb) {}

bool VulkanCommandBuffer::beginRecording() {
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    return vkBeginCommandBuffer(cb_, &info) == VK_SUCCESS;
}

void VulkanCommandBuffer::draw(uint32_t vertex_count) {
    vkCmdDraw(cb_, vertex_count, 1, 0, 0);
}

bool VulkanCommandBuffer::endRecording() {
    return vkEndCommandBuffer(cb_) == VK_SUCCESS;
}
