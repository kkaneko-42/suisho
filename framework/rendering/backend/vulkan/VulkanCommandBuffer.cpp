#include "rendering/backend/vulkan/VulkanCommandBuffer.h"

using namespace suisho;
using namespace suisho::backend;

VulkanCommandBuffer::VulkanCommandBuffer(VkCommandBuffer src) : cmd_(src) {}

bool VulkanCommandBuffer::beginRecording() {
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    
    return (vkBeginCommandBuffer(cmd_, &info) == VK_SUCCESS);
}

bool VulkanCommandBuffer::endRecording() {
    return (vkEndCommandBuffer(cmd_) == VK_SUCCESS);
}

bool VulkanCommandBuffer::reset() {
    return (vkResetCommandBuffer(cmd_, 0) == VK_SUCCESS);
}

void VulkanCommandBuffer::beginRenderPass(
    VkRenderPass pass, VkFramebuffer framebuffer,
    std::vector<VkClearValue> clear_info,
    const VkRect2D& area // FIXME: With (area_min, area_max)
) {
    VkRenderPassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    info.renderPass = pass;
    info.framebuffer = framebuffer;
    info.renderArea.offset = area.offset;
    info.renderArea.extent = area.extent;
    info.clearValueCount = static_cast<uint32_t>(clear_info.size());
    info.pClearValues = clear_info.data();

    vkCmdBeginRenderPass(cmd_, &info, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanCommandBuffer::endRenderPass() {
    vkCmdEndRenderPass(cmd_);
}

void VulkanCommandBuffer::setViewport(const VkViewport& viewport) {
    vkCmdSetViewport(cmd_, 0, 1, &viewport);
}

void VulkanCommandBuffer::setScissor(const VkRect2D& scissor) {
    vkCmdSetScissor(cmd_, 0, 1, &scissor);
}

void VulkanCommandBuffer::bindGraphicsPipeline(VkPipeline pipeline) {
    vkCmdBindPipeline(cmd_, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
}

void VulkanCommandBuffer::draw(uint32_t vertex_count) {
    vkCmdDraw(cmd_, vertex_count, 1, 0, 0);
}
