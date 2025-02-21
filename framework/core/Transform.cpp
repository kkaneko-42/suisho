#include "core/Transform.hpp"

using namespace suisho;

Transform::Transform(const Vec3& pos, const Quat& rot, const Vec3& scl)
: position(pos), rotation(rot), scale(scl) {}

Mat4 Transform::toMatrix() const {
    return Mat4::translate(position) * Mat4::rotate(rotation) * Mat4::scale(scale);
}
