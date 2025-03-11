#include "rendering/RenderingSystem.hpp"
#include "math/Vec3.hpp"
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

void RenderingSystem::update(SystemParams& params, Query<const Renderable, const Transform> query) {
    // FIXME
    if (renderer_.shouldWindowClose()) {
        renderer_.terminate();
        exit(0);
    }

    if (renderer_.beginFrame()) {
        query.forEach([this](const Renderable& renderable, const Transform& tf) {
            if (renderer_.getBoundMaterial() != renderable.material.get()) {
                renderer_.bindMaterial(*renderable.material);
            }

            renderer_.draw(tf.toMatrix());
        });

        renderer_.endFrame();
    }
}
