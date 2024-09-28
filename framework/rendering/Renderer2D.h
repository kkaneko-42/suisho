#ifndef SUISHO_RENDERING_RENDERER_2D_H_
#define SUISHO_RENDERING_RENDERER_2D_H_

#include "math/Mat4.h"
#include <memory>

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
    void draw();
    void terminate();

private:
    Renderer2DImpl* impl_;
};

} // namespace suisho

#endif // SUISHO_RENDERING_RENDERER_2D_H_
