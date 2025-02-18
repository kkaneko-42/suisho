#ifndef SUISHO_CORE_SYSTEM_TRAITS_H_
#define SUISHO_CORE_SYSTEM_TRAITS_H_

#include "core/EntityCommandBuffer.h"
#include "core/Query.h"

namespace suisho {

struct SystemParams {
    EntityCommandBuffer commands;
};

template <class F>
struct SystemTraits;

template <class T, class... S>
struct SystemTraits<void(*)(SystemParams&, Query<T, S...>)> {
    using QueryType = Query<T, S...>;
};

template <class T, class... S>
struct SystemTraits<std::function<void(SystemParams&, Query<T, S...>)>> {
    using QueryType = Query<T, S...>;
};

template <class C, class T, class... S>
struct SystemTraits<void(C::*)(SystemParams&, Query<T, S...>)> {
    using QueryType = Query<T, S...>;
};

template <class C, class T, class... S>
struct SystemTraits<void(C::*)(SystemParams&, Query<T, S...>) const> {
    using QueryType = Query<T, S...>;
};

template <class Lambda>
struct SystemTraits : SystemTraits<decltype(&Lambda::operator())> {};

} // namespace suisho

#endif
