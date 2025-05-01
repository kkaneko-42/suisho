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

    // FIXME: Renderiable must be const
    void update(SystemParams& params, Query<Renderable, const Transform> query);
};

} // namespace suisho

#endif // SUISHO_RENDERING_RENDERING_SYSTEM_H_
