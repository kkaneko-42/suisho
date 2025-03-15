#ifndef SUISHO_RENDERING_BACKEND_VULKAN_TEXTURE_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_TEXTURE_H_

#include "rendering/Texture.hpp"
#include "rendering/backend/vulkan/VulkanImage.hpp"

namespace suisho::backend {

struct VulkanTexture : public Texture {
    const void* getNativeHandle() const override {
        return this;
    }

    VulkanImage image;
    VkSampler sampler;
};

} // namespace suisho::backend

#endif // SUISHO_RENDERING_BACKEND_VULKAN_TEXTURE_H_
