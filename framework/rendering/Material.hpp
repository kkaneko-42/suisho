#ifndef SUISHO_RENDERING_MATERIAL_H_
#define SUISHO_RENDERING_MATERIAL_H_

#include "backend/vulkan/VulkanTexture.hpp"
#include "backend/vulkan/VulkanBindingLayout.hpp"
#include <memory>
#include <array>

namespace suisho {

// FIXME: Vulkan dependence
struct Material {
    std::shared_ptr<const backend::VulkanTexture> texture;
    std::array<VkDescriptorSet, 2 /* FIXME: Magic number. must be Renderer2D::kMaxFramesOverlapped */> binding_set;
    bool is_changed_;
};

} // namespace suisho

#endif
