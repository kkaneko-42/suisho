﻿#ifndef SUISHO_RENDERING_RENDERER_2D_H_
#define SUISHO_RENDERING_RENDERER_2D_H_

#include <string>
#include <array>
#include <memory>
#include "backend/vulkan/VulkanDevice.h"
#include "backend/vulkan/VulkanCommandBuffer.h"
#include "backend/vulkan/VulkanImage.h"
#include "rendering/Material.h"
#include "math/Mat4.h"
#include "math/Vec2.h"

namespace suisho {

struct Renderer2DImpl;

class Renderer2D {
public:
    static constexpr size_t kMaxFramesOverlapped = 2;
    static constexpr size_t kMaxObjectsCount = 1024;

    Renderer2D();
    ~Renderer2D();

    Renderer2D(const Renderer2D&) = delete;
    Renderer2D& operator=(const Renderer2D&) = delete;

    bool initialize();
    void terminate();
    bool shouldWindowClose() const; // FIXME
    bool beginFrame();
    void endFrame();

    void bindMaterial(const Material& material);
    void draw(const Mat4& xform);
    void drawText(const std::string& s, const Vec2& pos, float rot_degree, const Vec2& scale);


    // FIXME
    Material createMaterial(const std::string& texture_path);
    void destroyMaterial(Material& mat);

private:
    struct GlobalUniformBuffer {
        alignas(16) Mat4 view;
        alignas(16) Mat4 proj;
    };

    struct ObjectUniformBuffer {
        alignas(16) Mat4 model_to_world;
    };

    struct Frame {
        VkFence cmd_execution; // FIXME
        backend::VulkanCommandBuffer cmd_buf;
        backend::VulkanBuffer global_uniform;
        backend::VulkanBuffer object_uniform;
        void* object_uniform_data;
        VkDescriptorSet global_binding;
        VkDescriptorSet object_binding;
    };

    backend::VulkanDevice device_;
    size_t dynamic_alignment_;

    backend::VulkanBindingLayout global_layout_;
    backend::VulkanBindingLayout material_layout_;
    backend::VulkanBindingLayout object_layout_;
    Material default_material_;

    VkRenderPass render_pass_;
    VkPipelineLayout pipeline_layout_;
    VkPipeline pipeline_;

    backend::VulkanImage depth_buffer_;
    std::vector<VkFramebuffer> framebuffers_;

    std::array<Frame, kMaxFramesOverlapped> frames_;
    size_t current_frame_;
    uint32_t drawed_count_;

    void createDepthBuffer(uint32_t width, uint32_t height);
    void createFramebuffers(const std::vector<backend::VulkanImage>& swapchain_images);
};

} // namespace suisho

#endif // SUISHO_RENDERING_RENDERER_2D_H_
