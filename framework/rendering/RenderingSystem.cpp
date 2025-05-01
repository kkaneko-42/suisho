#include "rendering/RenderingSystem.hpp"
#include "rendering/Renderer2D.hpp"
#include "math/Vec3.hpp"
#include <stdexcept>

using namespace suisho;

RenderingSystem::RenderingSystem() {}
RenderingSystem::~RenderingSystem() {}

void RenderingSystem::update(SystemParams& params, Query<Renderable, const Transform> query) {
    auto& renderer = Renderer2D::get();
    // FIXME
    if (renderer.shouldWindowClose()) {
        renderer.terminate();
        exit(0);
    }

    if (renderer.beginFrame()) {
        query.forEach([this, &renderer](Renderable& renderable, const Transform& tf) {
            // FIXME
            auto& renderer = Renderer2D::get();
            if (renderable.material->is_changed[renderer.getCurrentFrameIndex()]) {
                renderer.getRenderingDevice()->updateBindingSet(
                    renderable.material->binding_set[renderer.getCurrentFrameIndex()],
                    0,
                    *renderable.material->texture,
                    VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
                );
                renderable.material->is_changed[renderer.getCurrentFrameIndex()] = false;
            }

            if (renderable.material.get() != renderer.getBoundMaterial()) {
                renderer.bindMaterial(*renderable.material);
            }

            renderer.draw(tf.toMatrix());
        });

        renderer.endFrame();
    }
}
