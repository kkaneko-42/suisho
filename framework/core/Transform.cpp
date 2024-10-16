#include "core/Transform.h"

using namespace suisho;

Transform::Transform(const Vec3& pos, const Vec3& scl) : position(pos), scale(scl) {}

Mat4 Transform::toMatrix() const {
    return Mat4::translate(position) * Mat4::scale(scale);
}
