#ifndef SUISHO_RENDERING_RENDERING_SYSTEM_H_
#define SUISHO_RENDERING_RENDERING_SYSTEM_H_

#include "core/SystemTraits.hpp"
#include "core/Transform.hpp"
#include "rendering/Renderer2D.hpp"

namespace suisho {

class RenderingSystem {
public:
    RenderingSystem();
    ~RenderingSystem();

    void update(SystemParams& params, Query<const Transform> query);
    void* getWindowHandle() { return renderer_.getWindowHandle(); } // FIXME

private:
    // FIXME: Any system dosen't have any state basically
    Renderer2D renderer_;
};

} // namespace suisho

#endif // SUISHO_RENDERING_RENDERING_SYSTEM_H_
