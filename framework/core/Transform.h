#ifndef SUISHO_CORE_TRANSFORM_H_
#define SUISHO_CORE_TRANSFORM_H_

#include "math/Vec3.h"
#include "math/Mat4.h"
#include "math/Quat.h"
#include "core/macros.h"

namespace suisho {

/// @brief Position, Rotation, Scale in 3D world
struct Transform {
    /// @brief Create Transform from the position, rotation, and scale
    /// @param pos position
    /// @param rot rotation
    /// @param scl scale
    Transform(const Vec3& pos = Vec3::kZero, const Quat& rot = Quat::kIdentity, const Vec3& scl = Vec3::kOne);

    /// @brief 3D position
    Vec3 position;

    /// @brief 3D rotation
    Quat rotation;

    /// @brief 3D scaling
    Vec3 scale;

    /// @brief Create the 3D affine transform matrix
    /// @return The matrix
    /// @todo Consider rotation
    Mat4 toMatrix() const;
};

SUISHO_COMPONENT(Transform, position, rotation, scale)

} // namespace suisho

#endif // SUISHO_CORE_TRANSFORM_H_
