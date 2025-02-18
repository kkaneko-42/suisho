#ifndef SUISHO_CORE_QUERY_H_
#define SUISHO_CORE_QUERY_H_

#include "core/World.h"

namespace suisho {

template <class T, class... S>
class Query {
public:
    Query(World& world) : world_(world) {}

    template <class F>
    void forEach(F&& f) {
        world_.iter<T, S...>(std::forward<F>(f));
    }

private:
    World& world_;
};

} // namespace suisho

#endif // SUISHO_CORE_QUERY_H_
