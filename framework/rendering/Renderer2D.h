#ifndef SUISHO_RENDERING_RENDERER_2D_H_
#define SUISHO_RENDERING_RENDERER_2D_H_

#include <string>
#include "rendering/Material.h"
#include "math/Mat4.h"
#include "math/Vec2.h"

namespace suisho {

struct Renderer2DImpl;

class Renderer2D {
public:
    Renderer2D();
    ~Renderer2D();

    Renderer2D(const Renderer2D&) = delete;
    Renderer2D& operator=(const Renderer2D&) = delete;

    bool initialize();
    bool shouldWindowClose() const; // FIXME
    bool beginFrame();
    void bindMaterial(const Material& material);
    void draw(const Mat4& xform);
    void drawText(const std::string& s, const Vec2& pos, float rot_degree, const Vec2& scale);
    void endFrame();
    void terminate();

    // FIXME
    Material createMaterial(const char* texture_path);
    Material createMaterial(const void* pixels, uint32_t width, uint32_t height, uint32_t pixel_bytes);

private:
    Renderer2DImpl* impl_;
};

} // namespace suisho

#endif // SUISHO_RENDERING_RENDERER_2D_H_
