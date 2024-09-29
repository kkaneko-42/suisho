#ifndef SUISHO_RENDERING_BACKEND_VULKAN_COMMAND_BUFFER_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_COMMAND_BUFFER_H_

#include "rendering/rhi/ICommandBuffer.h"
#include <vulkan/vulkan.h>

namespace suisho::backend {

class VulkanCommandBuffer : public rhi::ICommandBuffer {
public:
    // FIXME
    VulkanCommandBuffer(uint32_t& image_idx_dst, VkCommandBuffer cb);

    bool beginRecording() override;
    void draw(uint32_t vertex_count) override;
    bool endRecording() override;

    VkCommandBuffer& get() { return cb_; }

private:
    uint32_t& img_idx_;
    VkCommandBuffer cb_;
};

} // namespace suisho::backend

#endif // SUISHO_RENDERING_BACKEND_VULKAN_COMMAND_BUFFER_H_
