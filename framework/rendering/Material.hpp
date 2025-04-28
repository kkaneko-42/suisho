#ifndef SUISHO_RENDERING_MATERIAL_H_
#define SUISHO_RENDERING_MATERIAL_H_

#include "backend/vulkan/VulkanTexture.hpp"
#include "backend/vulkan/VulkanBindingLayout.hpp"
#include <memory>

namespace suisho {

// FIXME: Vulkan dependence
struct Material {
    std::shared_ptr<const backend::VulkanTexture> texture;
    VkDescriptorSet binding_set;
};

} // namespace suisho

#endif
