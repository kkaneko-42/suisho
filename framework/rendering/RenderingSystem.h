#ifndef SUISHO_RENDERING_RENDERING_SYSTEM_H_
#define SUISHO_RENDERING_RENDERING_SYSTEM_H_

#include "core/ISystem.h"
#include "core/Transform.h"
#include "rendering/Renderer2D.h"

namespace suisho {

class RenderingSystem : public ISystem<const Transform> {
public:
    RenderingSystem();
    ~RenderingSystem();

    void update(Params& params) override;
    void* getWindowHandle() { return renderer_.getWindowHandle(); } // FIXME

private:
    // FIXME: Any system dosen't have any state basically
    Renderer2D renderer_;
};

} // namespace suisho

#endif // SUISHO_RENDERING_RENDERING_SYSTEM_H_
