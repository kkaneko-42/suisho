#ifndef SUISHO_RENDERING_RENDERER_2D_H_
#define SUISHO_RENDERING_RENDERER_2D_H_

#include <string>
#include <array>
#include "backend/vulkan/VulkanDevice.h"
#include "backend/vulkan/VulkanCommandBuffer.h"
#include "rendering/Material.h"
#include "math/Mat4.h"
#include "math/Vec2.h"

namespace suisho {

struct Renderer2DImpl;

class Renderer2D {
public:
    static constexpr size_t kMaxFramesOverlapped = 2;

    Renderer2D();
    ~Renderer2D();

    Renderer2D(const Renderer2D&) = delete;
    Renderer2D& operator=(const Renderer2D&) = delete;

    bool initialize();
    void terminate();
    bool shouldWindowClose() const; // FIXME
    bool beginFrame();
    void bindMaterial(const Material& material);
    void draw(const Mat4& xform);
    void drawText(const std::string& s, const Vec2& pos, float rot_degree, const Vec2& scale);
    void endFrame();

    // FIXME
    Material createMaterial(const char* texture_path);
    Material createMaterial(const void* pixels, uint32_t width, uint32_t height, uint32_t pixel_bytes);

private:
    struct Frame {
        VkFence cmd_execution; // FIXME
        backend::VulkanCommandBuffer cmd_buf;
        VkFramebuffer framebuffer;
    };

    backend::VulkanDevice device_;

    VkRenderPass render_pass_;

    std::array<Frame, kMaxFramesOverlapped> frames_;
    size_t current_frame_;
};

} // namespace suisho

#endif // SUISHO_RENDERING_RENDERER_2D_H_
