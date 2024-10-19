#include "suisho.h"
#include <iostream>
#include <chrono>

using namespace suisho;

class ScalingSystem : public ISystem<std::tuple<Transform>> {
public:
    void update(Params& params) {
        params.query.forEach([](Transform& xform) {
            static auto begin_time = std::chrono::system_clock::now();
            const float duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin_time).count();
            xform.scale = std::abs(std::sin(duration * 1e-3)) * Vec3::kOne;
        });
    }
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

    ScalingSystem scaling;
    scheduler.addSystem(scaling);

    Gamepad pad(1);
    while (true) {
        pad.poll();
        std::cout << "ShoulderLeft: " << pad.isPressed(Gamepad::kShoulderLeft) << std::endl;
        std::cout << "ShoulderRight: " << pad.isPressed(Gamepad::kShoulderRight) << std::endl;
        scheduler.update(world);
    }

    return EXIT_SUCCESS;
}
