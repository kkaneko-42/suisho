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
     * @brief Erase all entities and components
     * 
     */
    void clear();

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
     * @return Reference to the constructed component. If T is an empty type, void
     * @throw std::invalid_argument e dosen't exists
     */
    template <class T, class... Args>
    decltype(auto) addComponent(Entity e, Args&&... args) {
        static_assert(std::is_constructible_v<T, Args...>, "\x1b[41m T must be constructible from Args \x1b[49m");
        if (!reg_.valid(e)) {
            throw std::invalid_argument(__func__ + std::string(": e is invalid"));
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
            throw std::invalid_argument(__func__ + std::string(": e is invalid"));
        }

        return reg_.remove<T, S...>(e);
    }

    /**
     * @brief Check if e has the specified components
     * 
     * @tparam T Component type
     * @tparam S Other component types
     * @param e Valid entity checked
     * @return True if e has all of the specified components. False otherwise.
     * @throw std::invalid_argument e dosen't exists
     */
    template <class T, class... S>
    bool hasComponent(Entity e) {
        if (!reg_.valid(e)) {
            throw std::invalid_argument(__func__ + std::string(": e is invalid"));
        }

        return reg_.all_of<T, S...>(e);
    }

    /**
     * @brief Get the reference to component attached to e
     * 
     * @tparam T Component type
     * @param e Valid eneity
     * @return Reference to the component attached to e. nullptr if e dosen't have T
     * @throw std::invalid_argument e dosen't exists
     */
    template <class T>
    T* getComponent(Entity e) {
        if (!reg_.valid(e)) {
            throw std::invalid_argument(__func__ + std::string(": e is invalid"));
        } else if (!hasComponent<T>(e)) {
            return nullptr;
        }

        return &reg_.get<T>(e);
    }

    /**
     * @brief Iterate components (and entities optional) 
     * 
     * @tparam T Component type attached to the iterated entities
     * @tparam S Other component types
     * @tparam F Callable object type (void(Entity, T&, S&...) or void(T&, S&...))
     * @param f Callable object. Form: 
     */
    template <class T, class... S, class... Exclude, class F>
    void iter(F&& f, std::tuple<Exclude...> = {}) {
        static_assert(
            std::is_invocable_v<F, Entity, T&, S&...> ||
            std::is_invocable_v<F, T&, S&...>,
            "\x1b[41m F must be callable by arguments (Entity, T&, S&...) or (T&, S&...) \x1b[49m"
        );
        reg_.view<T, S...>(entt::exclude_t<Exclude...>()).each(std::forward<F>(f));
    }

private:
    friend class WorldSerializer;

    entt::registry reg_;
};

} // namespace suisho

#endif // SUISHO_CORE_WORLD_H_
