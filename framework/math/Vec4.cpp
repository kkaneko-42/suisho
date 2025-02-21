#include "Vec4.hpp"
#include <cmath>
#include <stdexcept>

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

Vec4 Vec4::operator-() const {
    return Vec4(-x, -y, -z, -w);
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

float& Vec4::operator[](std::size_t idx) {
    if (idx > 4) {
        throw std::out_of_range("idx is out of range(4)");
    }

    return (idx == 0 ? x : idx == 1 ? y : z);
}

const float& Vec4::operator[](std::size_t idx) const {
    if (idx > 4) {
        throw std::out_of_range("idx is out of range(4)");
    }

    return (idx == 0 ? x : idx == 1 ? y : z);
}

float Vec4::length() const {
    return std::sqrt(lengthSqr());
}

float Vec4::lengthSqr() const {
    return x*x + y*y + z*z + w*w;
}

void Vec4::normalize() {
    const float lensqr = lengthSqr();
    if (lensqr == 0.0f) {
        x = y = z = w = 0.0f;
    } else {
        const float len = std::sqrt(lensqr);
        x /= len;
        y /= len;
        z /= len;
        w /= len;
    }
}

Vec4 Vec4::normalized() const {
    Vec4 v(*this);
    v.normalize();
    return v;
}

float Vec4::dot(const Vec4& rhs) const {
    return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
}
