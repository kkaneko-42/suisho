#include "rendering/RenderingSystem.h"
#include "math/Vec3.h"
#include <stdexcept>

using namespace suisho;

RenderingSystem::RenderingSystem() {
    if (!renderer_.initialize()) {
        throw std::runtime_error("Renderer2D initialization failed");
    }
}

RenderingSystem::~RenderingSystem() {
    renderer_.terminate();
}

void RenderingSystem::update(SystemParams& params, Query<const Transform> query) {
    static Material statue = renderer_.createMaterial(SUISHO_BUILTIN_ASSETS_DIR"/textures/statue.jpg");

    // FIXME
    if (renderer_.shouldWindowClose()) {
        renderer_.destroyMaterial(statue);
        renderer_.terminate();
        exit(0);
    }

    if (renderer_.beginFrame()) {
        renderer_.bindMaterial(statue);
        query.forEach([this](const Transform& xform) {
            renderer_.draw(xform.toMatrix());
        });

        renderer_.endFrame();
    }
}
