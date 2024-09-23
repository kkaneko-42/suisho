#include "SystemScheduler.h"

using namespace suisho;

void SystemScheduler::update(World& world) {
    auto& systems = systems_[static_cast<int>(SchedulePoint::kUpdate)];

    // TODO: Execute in parallel
    std::vector<EntityCommandBuffer> cmds(systems.size());
    auto cmd_itr = cmds.begin();
    for (auto& system : systems) {
        system(world, *(cmd_itr++));
    }

    for (auto& cmd : cmds) {
        cmd.submit(world);
    }
}
