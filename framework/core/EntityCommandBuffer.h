#ifndef SUISHO_CORE_ENTITY_COMMAND_BUFFER_H_
#define SUISHO_CORE_ENTITY_COMMAND_BUFFER_H_

#include <queue>
#include <functional>
#include "core/World.h"

namespace suisho {

class EntityCommandBuffer {
public:
    /**
     * @brief Create a new Entity
     * 
     * @tparam T Component types
     * @param components Components attached to the created entities
     * 
     * @see World::createEntity
     * @todo Support rvalue reference
     */
    template <class... T>
    void createEntity(const T&... components) {
        cmds_.push(std::bind(
            [](World& world, const T&... components) {
                auto e = world.createEntity();
                (world.addComponent<T>(e, components), ...);
            },
            std::placeholders::_1, components...
        ));
    }

    /**
     * @brief Destroy the specified entity
     * 
     * @param e Entity to destroy
     * @see World::destroyEntity
     */
    void destroyEntity(Entity e);

    /**
     * @brief Attach a component to e
     * 
     * @see World::addComponent
     */
    template <class T, class... Args>
    void addComponent(Entity e, Args&&... args) {
        cmds_.push(std::bind(
            [e](World& world, Args&&... args) {
                world.addComponent<T>(e, std::forward<Args>(args)...);
            },
            std::placeholders::_1, std::forward<Args>(args)...
        ));
    }

    /**
     * @brief Remove components T attached to e
     * 
     * @see World::removeComponent
     */
    template <class... T>
    void removeComponent(Entity e) {
        cmds_.push([e](World& world) {
            world.removeComponent<T...>(e);
        });
    }

    /**
     * @brief Execute the stored commands. After the executions, this buffer is cleared
     * 
     * @param world Executed on
     */
    void submit(World& world);

    /**
     * @brief Remove all commands stored
     * 
     */
    void clear();

private:
    /// @todo Fix frequent allocation
    std::queue<std::function<void(World&)>> cmds_;
};

} // namespace suisho

#endif // SUISHO_CORE_ENTITY_COMMAND_BUFFER_H_
