#include "suisho.h"
#include <iostream>

using namespace suisho;

int main() {
    World world;
    SystemScheduler scheduler;

    RenderingSystem rendering;
    scheduler.addSystem(rendering);

    while (true) {
        scheduler.update(world);
    }

    return EXIT_SUCCESS;
}
