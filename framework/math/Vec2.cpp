#include "Vec2.h"
#include <cmath>

using namespace suisho;

const Vec2 Vec2::kZero(0.0f, 0.0f);
const Vec2 Vec2::kOne(1.0f, 1.0f);
const Vec2 Vec2::kRight(1.0f, 0.0f);
const Vec2 Vec2::kLeft(-1.0f, 0.0f);
const Vec2 Vec2::kUp(0.0f, 1.0f);
const Vec2 Vec2::kDown(0.0f, -1.0f);

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float xval, float yval)
    : x(xval), y(yval) {}
Vec2::Vec2(const Vec2& src) : x(src.x), y(src.y) {}
Vec2::Vec2(Vec2&& src) noexcept : x(src.x), y(src.y) {}
Vec2::~Vec2() {}

Vec2& Vec2::operator=(const Vec2& rhs) {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
    }

    return *this;
}

Vec2& Vec2::operator=(Vec2&& rhs) noexcept {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
    }

    return *this;
}

bool Vec2::operator==(const Vec2& rhs) const {
    return (
        x == rhs.x &&
        y == rhs.y
    );
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
    Vec2 lhs(*this);
    return (lhs += rhs);
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
    Vec2 lhs(*this);
    return (lhs -= rhs);
}

Vec2& Vec2::operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vec2 Vec2::operator*(float s) const {
    Vec2 lhs(*this);
    return (lhs *= s);
}

Vec2& Vec2::operator*=(float s) {
    x *= s;
    y *= s;
    return *this;
}

Vec2 Vec2::operator/(float s) const {
    Vec2 lhs(*this);
    return (lhs /= s);
}

Vec2& Vec2::operator/=(float s) {
    x /= s;
    y /= s;
    return *this;
}

float Vec2::length() const {
    return std::sqrt(lengthSqr());
}

float Vec2::lengthSqr() const {
    return x*x + y*y;
}

void Vec2::normalize() {
    const float lensqr = lengthSqr();
    if (lensqr == 0.0f) {
        x = y = 0.0f;
    } else {
        const float len = std::sqrt(lensqr);
        x /= len;
        y /= len;
    }
}

Vec2 Vec2::normalized() const {
    Vec2 v(*this);
    v.normalize();
    return v;
}

float Vec2::dot(const Vec2& rhs) const {
    return x*rhs.x + y*rhs.y;
}
