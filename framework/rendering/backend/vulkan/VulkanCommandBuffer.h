#ifndef SUISHO_RENDERING_BACKEND_VULKAN_COMMAND_BUFFER_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_COMMAND_BUFFER_H_

#include <vulkan/vulkan.h>
#include <vector>

namespace suisho::backend {

class VulkanCommandBuffer {
public:
    VulkanCommandBuffer(VkCommandBuffer src = VK_NULL_HANDLE);

    VkCommandBuffer& get() { return cmd_; }
    const VkCommandBuffer& get() const { return cmd_; }

    bool beginRecording();
    bool endRecording();

    void beginRenderPass(
        VkRenderPass pass, VkFramebuffer framebuffer,
        std::vector<VkClearValue> clear_info,
        const VkRect2D& area // FIXME: With (area_min, area_max)
    );
    void endRenderPass();

    void setViewport(const VkViewport& viewport);
    void setScissor(const VkRect2D& scissor);
    void bindGraphicsPipeline(VkPipeline pipeline);

    void draw(uint32_t vertex_count);

private:
    VkCommandBuffer cmd_;
};

} // namespace suisho::backend

#endif // SUISHO_RENDERING_BACKEND_VULKAN_COMMAND_BUFFER_H_
