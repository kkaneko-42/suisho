#ifndef SUISHO_CORE_SYSTEM_SCHEDULER_H_
#define SUISHO_CORE_SYSTEM_SCHEDULER_H_

#include "core/SystemTraits.h"
#include <functional>
#include <vector>

namespace suisho {

enum class SchedulePoint {
    kUpdate,
    kSize,
};

/**
 * @brief Manage system execution and its ordering
 * 
 */
class SystemScheduler {
public:
    /**
     * @brief Register a new system.
     * If the system has already been added, add it separately.
     * 
     * @param system Registered system
     */
    template <class SystemType>
    void add(SchedulePoint point, SystemType&& system) {
        systems_[static_cast<int>(point)].emplace_back(
            [sys = std::forward<SystemType>(system)](World& world, SystemParams& params) {
                sys(params, typename SystemTraits<std::remove_reference_t<SystemType>>::QueryType(world));
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
    std::vector<std::function<void(World&, SystemParams&)>> systems_[static_cast<int>(SchedulePoint::kSize)];
};

} // namespace suisho

#endif
