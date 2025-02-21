#include "Vec3.hpp"
#include <cmath>

using namespace suisho;

const Vec3 Vec3::kZero(0.0f, 0.0f, 0.0f);
const Vec3 Vec3::kOne(1.0f, 1.0f, 1.0f);
const Vec3 Vec3::kRight(1.0f, 0.0f, 0.0f);
const Vec3 Vec3::kLeft(-1.0f, 0.0f, 0.0f);
const Vec3 Vec3::kUp(0.0f, 1.0f, 0.0f);
const Vec3 Vec3::kDown(0.0f, -1.0f, 0.0f);
const Vec3 Vec3::kBack(0.0f, 0.0f, 1.0f);
const Vec3 Vec3::kForward(0.0f, 0.0f, -1.0f);

Vec3::Vec3() : x(0), y(0), z(0) {}
Vec3::Vec3(float xval, float yval, float zval)
    : x(xval), y(yval), z(zval) {}
Vec3::Vec3(const Vec3& src) : x(src.x), y(src.y), z(src.z) {}
Vec3::Vec3(Vec3&& src) noexcept : x(src.x), y(src.y), z(src.z) {}
Vec3::~Vec3() {}

Vec3& Vec3::operator=(const Vec3& rhs) {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }

    return *this;
}

Vec3& Vec3::operator=(Vec3&& rhs) noexcept {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }

    return *this;
}

bool Vec3::operator==(const Vec3& rhs) const {
    return (
        x == rhs.x &&
        y == rhs.y &&
        z == rhs.z
    );
}

Vec3 Vec3::operator+(const Vec3& rhs) const {
    Vec3 lhs(*this);
    return (lhs += rhs);
}

Vec3& Vec3::operator+=(const Vec3& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator-(const Vec3& rhs) const {
    Vec3 lhs(*this);
    return (lhs -= rhs);
}

Vec3& Vec3::operator-=(const Vec3& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vec3 Vec3::operator*(float s) const {
    Vec3 lhs(*this);
    return (lhs *= s);
}

Vec3& Vec3::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vec3 Vec3::operator/(float s) const {
    Vec3 lhs(*this);
    return (lhs /= s);
}

Vec3& Vec3::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

float Vec3::length() const {
    return std::sqrt(lengthSqr());
}

float Vec3::lengthSqr() const {
    return x*x + y*y + z*z;
}

void Vec3::normalize() {
    const float lensqr = lengthSqr();
    if (lensqr == 0.0f) {
        x = y = z = 0.0f;
    } else {
        const float len = std::sqrt(lensqr);
        x /= len;
        y /= len;
        z /= len;
    }
}

Vec3 Vec3::normalized() const {
    Vec3 v(*this);
    v.normalize();
    return v;
}

float Vec3::dot(const Vec3& rhs) const {
    return x*rhs.x + y*rhs.y + z*rhs.z;
}

Vec3 Vec3::cross(const Vec3& rhs) const {
    return Vec3(
        y*rhs.z - z*rhs.y,
        z*rhs.x - x*rhs.z,
        x*rhs.y - y*rhs.x
    );
}
