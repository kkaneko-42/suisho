#ifndef SUISHO_RENDERING_BACKEND_VULKAN_BINDING_LAYOUT_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_BINDING_LAYOUT_H_

#include <unordered_map>
#include <vulkan/vulkan.h>

namespace suisho::backend {

struct VulkanBindingLayout {
    std::unordered_map<uint32_t, VkDescriptorType> bindings;
    VkDescriptorSetLayout layout;
};

} // namespace suisho::backend

#endif // SUISHO_RENDERING_BACKEND_VULKAN_BINDING_LAYOUT_H_
