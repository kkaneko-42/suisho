#ifndef SUISHO_RENDERING_RENDERING_SYSTEM_H_
#define SUISHO_RENDERING_RENDERING_SYSTEM_H_

#include "core/SystemTraits.hpp"
#include "core/Transform.hpp"
#include "rendering/Renderable.hpp"

namespace suisho {

class RenderingSystem {
public:
    RenderingSystem();
    ~RenderingSystem();

    void update(SystemParams& params, Query<const Renderable, const Transform> query);
    void* getWindowHandle(); // FIXME
};

} // namespace suisho

#endif // SUISHO_RENDERING_RENDERING_SYSTEM_H_
