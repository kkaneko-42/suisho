#ifndef SUISHO_CORE_QUERY_H_
#define SUISHO_CORE_QUERY_H_

#include "core/World.h"

namespace suisho {

template <class With, class Without = std::tuple<>>
class Query {
public:
    Query(World& world) : world_(world) {}

    template <class F>
    void forEach(F&& f) {
        forEachImpl(std::forward<F>(f), std::make_index_sequence<std::tuple_size_v<With>>());
    }

private:
    World& world_;

    template <class F, size_t... I>
    void forEachImpl(F&& f, std::index_sequence<I...>) {
        world_.iter<std::tuple_element_t<I, With>...>(std::forward<F>(f));
    }
};

} // namespace suisho

#endif // SUISHO_CORE_QUERY_H_
