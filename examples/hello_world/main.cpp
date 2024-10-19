#include "suisho.h"
#include <iostream>
#include <chrono>

using namespace suisho;

class GamepadControllSystem : public ISystem<std::tuple<Transform>> {
public:
    GamepadControllSystem() : pad_(0) {}

    void update(Params& params) {
        pad_.poll();
        const Vec2 xlate = pad_.getAxis2D(Gamepad::kLeftStick);
        const float scale = (pad_.getAxis1D(Gamepad::kTriggerRight) + 1.0f) / 2.0f;
        params.query.forEach([this, &xlate, &scale](Transform& xform) {
            xform.position += Vec3(xlate.x, xlate.y, 0.0f) * 1e-3;
            xform.scale = Vec3(scale, scale, 1.0f);
        });
    }

private:
    Gamepad pad_;
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

    GamepadControllSystem control;
    scheduler.addSystem(control);

    while (true) {
        scheduler.update(world);
    }

    return EXIT_SUCCESS;
}
