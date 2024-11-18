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
    const std::vector<VkClearValue>& clear_info,
    const VkExtent2D& area // FIXME: With (area_min, area_max)
) {
    VkRenderPassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    info.renderPass = pass;
    info.framebuffer = framebuffer;
    info.renderArea.offset = { 0, 0 };
    info.renderArea.extent = area;
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

void VulkanCommandBuffer::bindVertexBuffer(VkBuffer vertex) {
    VkDeviceSize offsets[1] = {0};
    vkCmdBindVertexBuffers(cmd_, 0, 1, &vertex, offsets);
}

void VulkanCommandBuffer::bindIndexBuffer(VkBuffer index) {
    vkCmdBindIndexBuffer(cmd_, index, 0, VK_INDEX_TYPE_UINT32);
}

void VulkanCommandBuffer::bindBindingSet(uint32_t index, VkDescriptorSet set, VkPipelineLayout layout) {
    vkCmdBindDescriptorSets(
        cmd_,
        VK_PIPELINE_BIND_POINT_GRAPHICS, layout,
        index, 1, &set,
        0, nullptr
    );
}

void VulkanCommandBuffer::bindBindingSetDynamic(uint32_t index, uint32_t offset, VkDescriptorSet set, VkPipelineLayout layout) {
    vkCmdBindDescriptorSets(
        cmd_,
        VK_PIPELINE_BIND_POINT_GRAPHICS, layout,
        index, 1, &set,
        1, &offset
    );
}

void VulkanCommandBuffer::draw(uint32_t vertex_count) {
    vkCmdDraw(cmd_, vertex_count, 1, 0, 0);
}

void VulkanCommandBuffer::drawInstanced(uint32_t vertex_count, uint32_t instance_count) {
    vkCmdDraw(cmd_, vertex_count, instance_count, 0, 0);
}

void VulkanCommandBuffer::drawIndexed(uint32_t index_count) {
    vkCmdDrawIndexed(cmd_, index_count, 1, 0, 0, 0);
}

void VulkanCommandBuffer::drawIndexedInstanced(uint32_t index_count, uint32_t instance_count) {
    vkCmdDrawIndexed(cmd_, index_count, instance_count, 0, 0, 0);
}
