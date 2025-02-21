#include "SystemScheduler.hpp"

using namespace suisho;

void SystemScheduler::update(World& world) {
    auto& systems = systems_[static_cast<int>(SchedulePoint::kUpdate)];

    // TODO: Execute in parallel
    std::vector<SystemParams> params(systems.size());
    auto param_itr = params.begin();
    for (auto& system : systems) {
        system(world, *(param_itr++));
    }

    for (auto& param : params) {
        param.commands.submit(world);
    }
}
