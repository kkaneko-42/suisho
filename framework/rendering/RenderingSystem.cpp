#include "rendering/RenderingSystem.hpp"
#include "rendering/Renderer2D.hpp"
#include "math/Vec3.hpp"
#include <stdexcept>

using namespace suisho;

RenderingSystem::RenderingSystem() {}
RenderingSystem::~RenderingSystem() {}

void RenderingSystem::update(SystemParams& params, Query<const Renderable, const Transform> query) {
    auto& renderer = Renderer2D::get();
    // FIXME
    if (renderer.shouldWindowClose()) {
        renderer.terminate();
        exit(0);
    }

    if (renderer.beginFrame()) {
        query.forEach([this, &renderer](const Renderable& renderable, const Transform& tf) {
            if (renderable.material.get() != renderer.getBoundMaterial()) {
                renderer.bindMaterial(*renderable.material);
            }

            renderer.draw(tf.toMatrix());
        });

        renderer.endFrame();
    }
}
