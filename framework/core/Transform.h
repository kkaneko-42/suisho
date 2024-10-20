﻿#ifndef SUISHO_CORE_TRANSFORM_H_
#define SUISHO_CORE_TRANSFORM_H_

#include "math/Vec3.h"
#include "math/Mat4.h"

namespace suisho {

/// @brief Position, Rotation, Scale in 3D world
/// @todo Rotation implement
struct Transform {
    /// @brief Create Transform from the position, rotation, and scale
    /// @param pos position
    /// @param scl scale
    /// @todo Rotation
    Transform(const Vec3& pos = Vec3::kZero, const Vec3& scl = Vec3::kOne);

    /// @brief 3D position
    Vec3 position;

    /// @brief 3D scaling
    Vec3 scale;

    /// @brief Create the 3D affine transform matrix
    /// @return The matrix
    Mat4 toMatrix() const;
};

} // namespace suisho

#endif // SUISHO_CORE_TRANSFORM_H_
