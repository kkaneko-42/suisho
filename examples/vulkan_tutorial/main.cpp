#include "suisho.h"
#include <iostream>

using namespace suisho;

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

    while (true) {
        scheduler.update(world);
    }

    return EXIT_SUCCESS;
}
