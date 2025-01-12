#ifndef SUISHO_CORE_ISYSTEM_H_
#define SUISHO_CORE_ISYSTEM_H_

#include "core/Query.h"
#include "core/EntityCommandBuffer.h"

namespace suisho {

/**
 * @brief System interface
 * 
 * @tparam T Iterated component type
 * @tparam S Other iterated component types
 * 
 */
template <class T, class... S>
struct ISystem {
    /**
     * @brief Interface to the world
     */
    struct Params {
        EntityCommandBuffer commands;
        Query<std::tuple<T, S...>> query;
    };

    /**
     * @brief Destructor
     */
    virtual ~ISystem() {}

    /**
     * @brief Called every frame
     * 
     * @param params System parameters
     */
    virtual void update(Params& params) = 0;
};

} // namespace suisho

#endif // SUISHO_CORE_ISYSTEM_H_
