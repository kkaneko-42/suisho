#include "core/World.h"

using namespace suisho;

Entity World::createEntity() {
    return reg_.create();
}

void World::destroyEntity(Entity e) {
    reg_.destroy(e);
}
