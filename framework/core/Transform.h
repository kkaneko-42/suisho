﻿#ifndef SUISHO_CORE_TRANSFORM_H_
#define SUISHO_CORE_TRANSFORM_H_

#include "math/Vec3.h"
#include "math/Mat4.h"

namespace suisho {

/// @brief Position, Rotation, Scale in 3D world
/// @todo Rotation implement
struct Transform {
    /// @brief 3D position
    Vec3 position;

    /// @brief 3D scaling
    Vec3 scale;

    /// @brief Create the 3D affine transform matrix
    /// @return The matrix
    Mat4 toMatrix() const {
        return Mat4::translate(position) * Mat4::scale(scale);
    }
};

} // namespace suisho

#endif // SUISHO_CORE_TRANSFORM_H_
