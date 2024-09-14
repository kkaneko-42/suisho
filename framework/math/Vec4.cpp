#include "Vec4.h"

using namespace suisho;

const Vec4 Vec4::kZero(0.0f, 0.0f, 0.0f, 0.0f);
const Vec4 Vec4::kOne(1.0f, 1.0f, 1.0f, 1.0f);

Vec4::Vec4() : x(0), y(0), z(0), w(0) {}
Vec4::Vec4(float xval, float yval, float zval, float wval)
    : x(xval), y(yval), z(zval), w(wval) {}
Vec4::Vec4(const Vec4& src) : x(src.x), y(src.y), z(src.z), w(src.w) {}
Vec4::Vec4(Vec4&& src) noexcept : x(src.x), y(src.y), z(src.z), w(src.w) {}
Vec4::~Vec4() {}

Vec4& Vec4::operator=(const Vec4& rhs) {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
    }

    return *this;
}

Vec4& Vec4::operator=(Vec4&& rhs) noexcept {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
    }

    return *this;
}

bool Vec4::operator==(const Vec4& rhs) const {
    return (
        x == rhs.x &&
        y == rhs.y &&
        z == rhs.z &&
        w == rhs.w
    );
}

Vec4 Vec4::operator+(const Vec4& rhs) const {
    Vec4 lhs(*this);
    return (lhs += rhs);
}

Vec4& Vec4::operator+=(const Vec4& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

Vec4 Vec4::operator-(const Vec4& rhs) const {
    Vec4 lhs(*this);
    return (lhs -= rhs);
}

Vec4& Vec4::operator-=(const Vec4& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

Vec4 Vec4::operator*(float s) const {
    Vec4 lhs(*this);
    return (lhs *= s);
}

Vec4& Vec4::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
}

Vec4 Vec4::operator/(float s) const {
    Vec4 lhs(*this);
    return (lhs /= s);
}

Vec4& Vec4::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
}
