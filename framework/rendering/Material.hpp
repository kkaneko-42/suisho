#ifndef SUISHO_RENDERING_MATERIAL_H_
#define SUISHO_RENDERING_MATERIAL_H_

#include "backend/vulkan/VulkanTexture.hpp"
#include "backend/vulkan/VulkanBindingLayout.hpp"

namespace suisho {

// FIXME: Vulkan dependence
struct Material {
    backend::VulkanTexture texture;
    VkDescriptorSet binding_set;
};

} // namespace suisho

#endif
