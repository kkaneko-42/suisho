﻿#include "suisho.h"
#include <iostream>
#include <chrono>
#define USE_GAMEPAD 0

using namespace suisho;

class ControllSystem : public ISystem<std::tuple<Transform>> {
public:
#if USE_GAMEPAD
    ControllSystem() : pad_(0) {}
#else
    ControllSystem(void* win) : keyboard_(win) {}
#endif

    void update(Params& params) {
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

        params.query.forEach([this, &xlate](Transform& xform) {
            xform.position += Vec3(xlate.x, xlate.y, 0.0f) * 1e-3;
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
    World world;

    const float scale = 0.2f;
    const int objects_count_x = 8;
    const int objects_count_y = 8;
    for (int y = -objects_count_y / 2; y < objects_count_y / 2; ++y) {
        for (int x = -objects_count_x / 2; x < objects_count_x / 2; ++x) {
            auto e = world.createEntity();
            const Vec3 pos = (scale + 0.01f) * Vec3(x, y, 0.0f);
            world.addComponent<Transform>(e, pos, scale * Vec3::kOne);
        }
    }

    return world;
}

int main() {
    World world = createWorld();
    SystemScheduler scheduler;

    RenderingSystem rendering;
    scheduler.addSystem(rendering);

    ControllSystem control(rendering.getWindowHandle());
    scheduler.addSystem(control);

    while (true) {
        scheduler.update(world);
    }

    return EXIT_SUCCESS;
}
