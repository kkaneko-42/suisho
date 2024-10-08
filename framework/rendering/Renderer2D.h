﻿#ifndef SUISHO_RENDERING_RENDERER_2D_H_
#define SUISHO_RENDERING_RENDERER_2D_H_

#include "rendering/Material.h"
#include "math/Mat4.h"

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
    void setLocalToWorld(const Mat4& xform);
    void draw();
    void endFrame();
    void terminate();

    Material createMaterial(const char* texture_path);

private:
    Renderer2DImpl* impl_;
};

} // namespace suisho

#endif // SUISHO_RENDERING_RENDERER_2D_H_
