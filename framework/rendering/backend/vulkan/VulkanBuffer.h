#ifndef SUISHO_RENDERING_BACKEND_VULKAN_BUFFER_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_BUFFER_H_

#include <vulkan/vulkan.h>

namespace suisho::backend {

struct VulkanBuffer {
    VkDeviceSize size;
    VkBuffer buffer;
    VkDeviceMemory memory;
    void* mapped;
};

} // namespace suisho::backend

#endif // SUISHO_RENDERING_BACKEND_VULKAN_BUFFER_H_
