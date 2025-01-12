#ifndef SUISHO_CORE_SYSTEM_SCHEDULER_H_
#define SUISHO_CORE_SYSTEM_SCHEDULER_H_

#include "core/ISystem.h"
#include <functional>
#include <vector>

namespace suisho {

/**
 * @brief Manage system execution and its ordering
 * 
 */
class SystemScheduler {
public:
    enum class SchedulePoint {
        kUpdate,
        kSize,
    };

    /**
     * @brief Register a new system.
     * If the system has already been added, add it separately.
     * 
     * @tparam With Component types tuple iterated by the system
     * @tparam Without Component types tuple excluded the iterating
     * @param system Registered system
     */
    template <class T, class... S>
    void addSystem(ISystem<T, S...>& system) {
        systems_[static_cast<int>(SchedulePoint::kUpdate)].push_back(
            [&system](World& world, EntityCommandBuffer& cmd) {
                typename ISystem<T, S...>::Params params{ {}, {world} };
                system.update(params);
                cmd = std::move(params.commands);
            }
        );
    }

    /**
     * @brief Execute update() method with all registered systems
     * 
     * @param world Target world
     */
    void update(World& world);

private:
    std::vector<std::function<void(World&, EntityCommandBuffer&)>> systems_[static_cast<int>(SchedulePoint::kSize)];
};

} // namespace suisho

#endif
