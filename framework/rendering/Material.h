#ifndef SUISHO_RENDERING_MATERIAL_H_
#define SUISHO_RENDERING_MATERIAL_H_

#include <vulkan/vulkan.h>

namespace suisho {

struct Texture {
    VkImage image;
    VkDeviceMemory memory;
    VkImageView view;
    VkSampler sampler;
};

struct Material {
    Texture texture;
    VkDescriptorSetLayout layout;
    VkDescriptorSet descriptor;
};

} // namespace suisho

#endif
