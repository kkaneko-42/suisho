#include "math/Quat.h"
#include "math/Vec3.h"
#include <utility>
#include "core/exceptions.h"

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
    throw NotImplementedException("Quat * Quat");
}

Quat& Quat::operator*=(const Quat& q) {
    throw NotImplementedException("Quat * Quat");
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
    throw NotImplementedException("Quat::angleAxis");
    return Quat();
}

Quat Quat::lerp(const Quat& a, const Quat& b, float t) {
    throw NotImplementedException("Quat::lerp");
    return Quat();
}

Quat Quat::slerp(const Quat& a, const Quat& b, float t) {
    throw NotImplementedException("Quat::slerp");
    return Quat();
}
