#ifndef SUISHO_CORE_WORLD_H_
#define SUISHO_CORE_WORLD_H_

#include <entt/entity/registry.hpp>

namespace suisho {

using Entity = entt::entity;

/**
 * @brief Entities, components and systems stored here.
 */
class World {
public:
    /**
     * @brief Create a new Entity and add to this world
     *
     * @return Added eneity
     */
    Entity createEntity();

    /**
     * @brief Destroy the given entity. All components attached to e are also destroyed.
     * 
     * @param e Valid entity to destroy
     * @throw std::invalid_argument e dosen't exists
     */
    void destroyEntity(Entity e);

    /**
     * @brief Add constructed component and attached to e. If T has already attached to e, replace it.
     * 
     * @tparam T Component type
     * @tparam Args Component construction param types
     * @param e Valid eneity to attach
     * @param args Constructor params of T
     * @throw std::invalid_argument e dosen't exists
     */
    template <class T, class... Args>
    T& addComponent(Entity e, Args&&... args) {
        if (!reg_.valid(e)) {
            throw std::invalid_argument();
        }

        return reg_.emplace_or_replace<T>(e, std::forward<Args>(args)...);
    }

    /**
     * @brief Remove components from e
     * 
     * @tparam T Component type to remove
     * @tparam S Other component types to remove
     * @param e Valid entity
     * @return Actually removed components count
     * @throw std::invalid_argument e dosen't exists
     */
    template <class T, class... S>
    std::size_t removeComponent(Entity e) {
        if (!reg_.valid(e)) {
            throw std::invalid_argument();
        }

        return reg_.remove<T, S...>(e);
    }

private:
    entt::registry reg_;
};

} // namespace suisho

#endif // SUISHO_CORE_WORLD_H_
