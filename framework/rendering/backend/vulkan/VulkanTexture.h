#ifndef SUISHO_RENDERING_BACKEND_VULKAN_TEXTURE_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_TEXTURE_H_

#include "rendering/backend/vulkan/VulkanImage.h"

namespace suisho::backend {

struct VulkanTexture {
    VulkanImage image;
    VkSampler sampler;
};

} // namespace suisho::backend

#endif // SUISHO_RENDERING_BACKEND_VULKAN_TEXTURE_H_
