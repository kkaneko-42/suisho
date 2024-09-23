#ifndef SUISHO_CORE_ISYSTEM_H_
#define SUISHO_CORE_ISYSTEM_H_

#include "core/Query.h"
#include "core/EntityCommandBuffer.h"

namespace suisho {

/**
 * @brief System interface
 * 
 * @tparam With Component types tuple iterated by the system
 * @tparam Without Component types tuple excluded the iterating
 */
template <class With, class Without = std::tuple<>>
struct ISystem {
    /**
     * @brief Interface to the world
     */
    struct Params {
        EntityCommandBuffer commands;
        Query<With, Without> query;
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
