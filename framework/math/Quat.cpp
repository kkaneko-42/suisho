#include "math/Quat.hpp"
#include "math/Vec3.hpp"
#include "core/exceptions.hpp"
#include <utility>
#include <cmath>


using namespace suisho;

const Quat Quat::kIdentity(0.0f, 0.0f, 0.0f, 1.0f);

Quat::Quat() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

Quat::Quat(float xx, float yy, float zz, float ww)
: x(xx), y(yy), z(zz), w(ww) {}

Quat::Quat(const Quat& q)
: x(q.x), y(q.y), z(q.z), w(q.w) {}

Quat::Quat(Quat&& q)
: x(q.x), y(q.y), z(q.z), w(q.w) {}

Quat::~Quat() {}

Quat& Quat::operator=(const Quat& q) {
    if (this != &q) {
        x = q.x;
        y = q.y;
        z = q.z;
        w = q.w;
    }

    return *this;
}

Quat& Quat::operator=(Quat&& q) {
    if (this != &q) {
        x = q.x;
        y = q.y;
        z = q.z;
        w = q.w;
    }

    return *this;
}

Quat Quat::operator*(const Quat& q) const {
    return Quat(
        w*q.x - z*q.y + y*q.z + x*q.w,
        z*q.x + w*q.y - x*q.z + y*q.w,
       -y*q.x + x*q.y + w*q.z + z*q.w,
       -x*q.x - y*q.y - z*q.z + w*q.w 
    );
}

Quat& Quat::operator*=(const Quat& q) {
    // FIXME: Performance concern
    *this = *this * q;
    return *this;
}

Vec3 Quat::operator*(const Vec3& vec) const {
    throw NotImplementedException("Quat * Vec3");
    return Vec3();
}

bool Quat::operator==(const Quat& q) const {
    return (
        x == q.x &&
        y == q.y &&
        z == q.z &&
        w == q.w
    );
}

Quat Quat::fromEuler(float x, float y, float z) {
    throw NotImplementedException("Quat::fromEuler");
    return Quat();
}

Quat Quat::fromEuler(const Vec3& degree) {
    throw NotImplementedException("Quat::fromEuler");
    return Quat();
}

Quat Quat::angleAxis(float degree, const Vec3& axis) {
    const float angle_half = degree / 2.0f;
    const float s = std::sin(angle_half);
    return Quat(
        axis.x * s,
        axis.y * s,
        axis.z * s,
        std::cos(angle_half)
    );
}

Quat Quat::lerp(const Quat& a, const Quat& b, float t) {
    throw NotImplementedException("Quat::lerp");
    return Quat();
}

Quat Quat::slerp(const Quat& a, const Quat& b, float t) {
    throw NotImplementedException("Quat::slerp");
    return Quat();
}
