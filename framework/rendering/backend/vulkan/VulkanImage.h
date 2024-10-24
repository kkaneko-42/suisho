#ifndef SUISHO_RENDERING_BACKEND_VULKAN_IMAGE_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_IMAGE_H_

#include <vulkan/vulkan.h>

namespace suisho::backend {
    struct VulkanImage {
        VkImage image;
        VkDeviceMemory memory;
        VkImageView view;

        VkFormat format;
        VkExtent2D extent;
        VkImageLayout layout;
    };
}

#endif // SUISHO_RENDERING_BACKEND_VULKAN_IMAGE_H_
