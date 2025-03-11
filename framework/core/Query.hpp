#ifndef SUISHO_CORE_QUERY_H_
#define SUISHO_CORE_QUERY_H_

#include "core/World.hpp"

namespace suisho {

template <class T, class... S>
class Query {
public:
    Query(World& world) : world_(world) {}

    template <class F>
    void forEach(F&& f) {
        if constexpr (std::is_invocable_v<F, Entity, T&, S&...>) {
            world_.iter<Entity, T, S...>(std::forward<F>(f));
        } else {
            world_.iter<T, S...>(std::forward<F>(f));
        }
    }

private:
    World& world_;
};

} // namespace suisho

#endif // SUISHO_CORE_QUERY_H_
