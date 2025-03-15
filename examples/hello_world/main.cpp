#include "suisho.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#define USE_GAMEPAD 0

using namespace suisho;

struct IsCenter {};

class ControllSystem {
public:
#if USE_GAMEPAD
    ControllSystem() : pad_(0) {}
#else
    ControllSystem(void* win) : keyboard_(win) {}
#endif

    void update(SystemParams& params, Query<Transform>& query) {
#if USE_GAMEPAD
        pad_.poll();
        const Vec2 xlate = pad_.getAxis2D(Gamepad::kLeftStick);
#else
        keyboard_.poll();
        const Vec2 xlate = Vec2(
            keyboard_.isPressed(Keyboard::kArrowRight) - keyboard_.isPressed(Keyboard::kArrowLeft),
            keyboard_.isPressed(Keyboard::kArrowUp) - keyboard_.isPressed(Keyboard::kArrowDown)
        );
#endif

        query.forEach([this, &xlate, &params](Entity e, Transform& xform) {
            xform.position += Vec3(xlate.x, xlate.y, 0.0f) * 1e-2;
            xform.rotation *= Quat::angleAxis(1e-2, Vec3::kBack);
            if (params.world.hasComponent<IsCenter>(e)) {
                xform.rotation *= Quat::angleAxis(1e-2, Vec3::kBack);
            }
        });
    }

private:
#if USE_GAMEPAD
    Gamepad pad_;
#else
    Keyboard keyboard_;
#endif
};

static World createWorld() {
    auto& renderer = Renderer2D::get();
    auto material = std::make_shared<Material>(renderer.createMaterial(SUISHO_BUILTIN_ASSETS_DIR"/textures/statue.jpg"));

    World world;
    const float scale = 0.2f;
    const int objects_count_x = 8;
    const int objects_count_y = 8;
    for (int y = -objects_count_y / 2; y < objects_count_y / 2; ++y) {
        for (int x = -objects_count_x / 2; x < objects_count_x / 2; ++x) {
            auto e = world.createEntity();
            const Vec3 pos = (scale + 0.01f) * Vec3(x, y, 0.0f);
            world.addComponent<Transform>(e, pos, Quat::kIdentity, scale * Vec3::kOne);
            world.addComponent<Renderable>(e, material);
            if (y == 0 && x == 0) {
                world.addComponent<IsCenter>(e);
                world.getComponent<Renderable>(e)->material = std::make_shared<Material>(
                    renderer.createMaterial(SUISHO_BUILTIN_ASSETS_DIR"/textures/mandrill.png")
                );
            }
        }
    }

    return world;
}

int main() {
    RenderingSystem rendering;
    SceneManager::activate(createWorld());

    SystemScheduler scheduler;
    scheduler.add(SchedulePoint::kUpdate, [&rendering](SystemParams& params, Query<const Renderable, const Transform> query) {
        rendering.update(params, query);
    });

#if USE_GAMEPAD
    ControllSystem control;
#else
    ControllSystem control(rendering.getWindowHandle());
#endif
    scheduler.add(SchedulePoint::kUpdate, [&control](SystemParams& params, Query<Transform> query) {
        control.update(params, query);
    });

    while (true) {
        scheduler.update(SceneManager::current());
    }

    return EXIT_SUCCESS;
}
