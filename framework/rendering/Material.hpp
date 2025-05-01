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
    std::array<bool, 2> is_changed;

    void setTexture(const std::shared_ptr<backend::VulkanTexture> tex) {
        texture = tex;
        is_changed[0] = is_changed[1] = true;
    }
};

} // namespace suisho

#endif
