#ifndef SUISHO_CORE_SCENE_MANAGER_H_
#define SUISHO_CORE_SCENE_MANAGER_H_

#include "core/World.hpp"

namespace suisho {

/**
 * @brief Static class that manages World Life Cycle
 * @note We plan to define Scene Class, which combines the current "World" and "SystemScheduler".
 *       Because the name of World is not consistent, it is on hold.
 */
class SceneManager {
public:
    enum class LoadMode {
        /// @brief Activate the loaded scene
        kActivate,
        /// @brief Cache the loaded scene without actively
        kCache,
        /// @brief Combine the loaded scene to the active scene
        kMerge
    };

    /**
     * @brief Activate the scene
     * 
     * @param world Scene to be activated
     */
    static void activate(World&& world);

    /**
     * @brief Get an active scene now
     * 
     * @return Currently active scene
     */
    static World& current();

private:
    static World current_;
};

} // namespace suisho

#endif
