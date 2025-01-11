#include "core/World.h"
#include <stdexcept>

using namespace suisho;

void World::clear() {
    reg_.clear();
}

Entity World::createEntity() {
    return reg_.create();
}

void World::destroyEntity(Entity e) {
    if (!reg_.valid(e)) {
        throw std::invalid_argument(__func__ + std::string(": e is invalid"));
    }

    reg_.destroy(e);
}
