#include "math/Mat4.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/Quat.h"
#include "core/exceptions.h"
#include <cmath>

using namespace suisho;

const Mat4 Mat4::kI({
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
});

Mat4::Mat4() : values_{ {}, {}, {}, {} } {}
Mat4::Mat4(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33
) : values_{
    { m00, m01, m02, m03 },
    { m10, m11, m12, m13 },
    { m20, m21, m22, m23 },
    { m30, m31, m32, m33 } 
} {}

Mat4::Mat4(const Mat4& other) : values_{
    { other.values_[0][0], other.values_[0][1], other.values_[0][2], other.values_[0][3] },
    { other.values_[1][0], other.values_[1][1], other.values_[1][2], other.values_[1][3] },
    { other.values_[2][0], other.values_[2][1], other.values_[2][2], other.values_[2][3] },
    { other.values_[3][0], other.values_[3][1], other.values_[3][2], other.values_[3][3] },
} {}

Mat4::Mat4(Mat4&& other) noexcept : values_{
    { other.values_[0][0], other.values_[0][1], other.values_[0][2], other.values_[0][3] },
    { other.values_[1][0], other.values_[1][1], other.values_[1][2], other.values_[1][3] },
    { other.values_[2][0], other.values_[2][1], other.values_[2][2], other.values_[2][3] },
    { other.values_[3][0], other.values_[3][1], other.values_[3][2], other.values_[3][3] },
} {}

Mat4& Mat4::operator=(const Mat4& rhs) {
    if (this != &rhs) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                values_[i][j] = rhs.values_[i][j];
            }
        }
    }

    return *this;
}

Mat4& Mat4::operator=(Mat4&& rhs) noexcept {
    if (this != &rhs) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                values_[i][j] = rhs.values_[i][j];
            }
        }
    }

    return *this;
}

Mat4 Mat4::translate(const Vec3& xlate) {
    return Mat4(
        1.0f, 0.0f, 0.0f, xlate.x,
        0.0f, 1.0f, 0.0f, xlate.y,
        0.0f, 0.0f, 1.0f, xlate.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Mat4 Mat4::rotate(const Quat& q) {
    const float xx = q.x * q.x;
    const float yy = q.y * q.y;
    const float zz = q.z * q.z;
    const float xy = q.x * q.y;
    const float xz = q.x * q.z;
    const float yz = q.y * q.z;
    const float xw = q.w * q.x;
    const float yw = q.w * q.y;
    const float zw = q.w * q.z;

    return Mat4(
        1 - 2*(yy - zz), 2*(xy - zw), 2*(xz + yw), 0.0f,
        2*(xy + zw), 1 - 2*(xx + zz), 2*(yz - xw), 0.0f,
        2*(xz - yw), 2*(yz + xw), 1 - 2*(xx - yy), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Mat4 Mat4::rotate(float deg, const Vec3& axis) {
    constexpr float kPi = 3.1415926535; // FIXME
    const float rad = deg * kPi / 180.0f; // Angle in radius
    const float c = std::cos(rad);
    const float s = std::sin(rad);
    const float x = axis.x;
    const float y = axis.y;
    const float z = axis.z;

    return Mat4(
        x*x*(1 - c) + c, x*y*(1 - c) - z*s, x*z*(1 - c) + y*s, 0.0f,
        x*y*(1 - c) + z*s, y*y*(1 - c) + c, y*z*(1 - c) - x*s, 0.0f,
        x*z*(1 - c) - y*s, y*z*(1 - c) + x*s, z*z*(1 - c) + c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Mat4 Mat4::scale(const Vec3& s) {
    return Mat4(
        s.x , 0.0f, 0.0f, 0.0f,
        0.0f, s.y , 0.0f, 0.0f,
        0.0f, 0.0f, s.z , 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Mat4 Mat4::lookAt(const Vec3& from, const Vec3& to, const Vec3& up) {
    const Vec3 z = (from - to).normalized();
    const Vec3 x = up.cross(z).normalized();
    const Vec3 y = z.cross(x).normalized();
    const Mat4 rot(
        x.x, x.y, x.z, 0.0f,
        y.x, y.y, y.z, 0.0f,
        z.x, z.y, z.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    return rot * translate(-from);
}

Mat4 Mat4::ortho(double left, double right, double bottom, double top, double near, double far) {
    // TODO: impl
    throw NotImplementedException("Mat4::ortho()");
    return Mat4();
}

Mat4 Mat4::perspective(double fov, double aspect, double near, double far) {
    const double tan_fov = std::tan(fov * 3.14159265358979 / 180.0f / 2.0f);
    return Mat4(
        1 / (aspect * tan_fov), 0.0f, 0.0f, 0.0f,
        0.0f, 1 / tan_fov, 0.0f, 0.0f,
        0.0f, 0.0f, -(far + near) / (far - near), -(2 * far * near) / (far - near),
        0.0f, 0.0f, -1.0f, 0.0f
    );
}

Mat4 Mat4::inversed() const {
    Mat4 result = *this;
    result.inverse();
    return result;
}

void Mat4::inverse() {
    /// @todo impl
    throw NotImplementedException("Mat4::inverse()");
}

float Mat4::det() const {
    /// @todo impl
    throw NotImplementedException("Mat4::det()");
    return 0.0f;
}

Mat4 Mat4::operator*(const Mat4& rhs) const {
    Mat4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.values_[i][j] += values_[i][k] * rhs.values_[k][j];
            }
        }
    }

    return result;
}

Vec4 Mat4::operator*(const Vec4& rhs) const {
    Vec4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i] += values_[i][j] * rhs[j];
        }
    }

    return result;
}
