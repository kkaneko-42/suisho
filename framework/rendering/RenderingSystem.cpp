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

void RenderingSystem::update(Params& params) {
    static Material mandrill = renderer_.createMaterial(SUISHO_BUILTIN_ASSETS_DIR"/textures/mandrill.png");
    static Material statue = renderer_.createMaterial(SUISHO_BUILTIN_ASSETS_DIR"/textures/statue.jpg");
    if (renderer_.shouldWindowClose()) {
        exit(1);
    }

    if (renderer_.beginFrame()) {
        // With default material
        for (int32_t y = 0; y < 5; ++y) {
            for (int32_t x = 0; x < 5; ++x) {
                renderer_.draw(Mat4::scale(0.2f * Vec3::kOne) * Mat4::translate(1.1f * Vec3(x - 5, y - 5, 0.0f)));
            }
        }

        // With mandrill
        renderer_.bindMaterial(mandrill);
        for (int32_t y = 0; y < 5; ++y) {
            for (int32_t x = 5; x < 10; ++x) {
                renderer_.draw(Mat4::scale(0.2f * Vec3::kOne) * Mat4::translate(1.1f * Vec3(x - 5, y - 5, 0.0f)));
            }
        }

        // With statue
        renderer_.bindMaterial(statue);
        for (int32_t y = 0; y < 5; ++y) {
            for (int32_t x = 10; x < 15; ++x) {
                renderer_.draw(Mat4::scale(0.2f * Vec3::kOne) * Mat4::translate(1.1f * Vec3(x - 5, y - 5, 0.0f)));
            }
        }

        renderer_.drawText("Hello, World!", Vec2::kZero, 0.0f, Vec2::kZero);

        renderer_.endFrame();
    }
}
