#include "core/SceneManager.h"
#include "core/WorldSerializer.h"

using namespace suisho;

World SceneManager::current_;

void SceneManager::activate(World&& world) {
    current_ = std::move(world);
}

World& SceneManager::current() { return current_; }
