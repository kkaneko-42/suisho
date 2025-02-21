#include "core/EntityCommandBuffer.hpp"

using namespace suisho;

void EntityCommandBuffer::destroyEntity(Entity e) {
    cmds_.push([e](World& world) { world.destroyEntity(e); });
}

void EntityCommandBuffer::submit(World& world) {
    while (!cmds_.empty()) {
        cmds_.front()(world);
        cmds_.pop();
    }
}

void EntityCommandBuffer::clear() {
    decltype(cmds_)().swap(cmds_);;
}
