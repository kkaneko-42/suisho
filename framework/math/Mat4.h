#ifndef SUISHO_MATH_MAT4_H_
#define SUISHO_MATH_MAT4_H_

namespace suisho {

class Vec3;
class Vec4;

/**
 * @brief Matrix 4x4
 */
class Mat4 {
public:

    /// @brief Identity matrix
    static const Mat4 kI;

    /**
     * @brief Initialize all elements to zero
     * 
     */
    constexpr Mat4();

    /**
     * @brief Initialize all elements to the specified values
     * 
     * @param values Elements value
     */
    constexpr Mat4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33
    );

    /**
     * @brief Copy constructor
     * 
     * @param other Copy target
     */
    Mat4(const Mat4& other);

    /**
     * @brief Move constructor
     * 
     * @param other Moved value
     */
    Mat4(Mat4&& other) noexcept;

    ~Mat4() = default;

    /**
     * @brief Copy assignation operator overload
     * 
     * @param rhs Right hand side value
     * @return *this
     */
    Mat4& operator=(const Mat4& rhs);

    /**
     * @brief Move assignation operator overload
     * 
     * @param rhs Right hand side value
     * @return *this
     */
    Mat4& operator=(Mat4&& rhs) noexcept;

    /**
     * @brief Create a translation matrix
     * 
     * @param xlate Translation value
     * @return Created matrix
     */
    static Mat4 translate(const Vec3& xlate);

    /**
     * @brief Create a scaling matrix
     * 
     * @param scale Scaling value
     * @return Created matrix
     */
    static Mat4 scale(const Vec3& scale);

    /**
     * @brief Create a look at matrix
     * 
     * @param from Eye position
     * @param to Target position
     * @param up Up direction
     * @return Created matrix
     */
    static Mat4 lookAt(const Vec3& from, const Vec3& to, const Vec3& up = Vec3::kUp);

    /**
     * @brief Creates an orthographic projection matrix
     * 
     * @param left, right, bottom, top, near, far clipping planes info
     * @return The orthographic projection matrix
     */
    static Mat4 ortho(double left, double right, double bottom, double top, double near, double far);

    /**
     * @brief Creates a perspective projection matrix
     * 
     * @param fov Vertical field-of-view in degrees
     * @param aspect Aspect ratio
     * @param near Near clipping plane
     * @param far Far clipping plane
     * @return The perspective projection matrix
     */
    static Mat4 perspective(double fov, double aspect, double near, double far);

    /**
     * @brief Create a inversed matrix
     * 
     * @return Inverse of this
     */
    Mat4 inversed() const;

    /**
     * @brief Inverse this matrix
     * 
     */
    void inverse();

    /**
     * @return Determinant of this
     */
    float det() const;

    /**
     * @return Pointer to the head(values_[0][0])
     */
    float* data() { return &values_[0][0]; }

    /**
     * @return Const pointer to the head(values_[0][0])
     */
    const float* data() const { return &values_[0][0]; }

    /**
     * @brief Multiply the matrices
     * 
     * @param rhs Right hand side value
     * @return Result of this * rhs
     */
    Mat4 operator*(const Mat4& rhs) const;

    Vec4 operator*(const Vec4& rhs) const;

private:
    float values_[4][4];
};

} // namespace suisho

#endif // SUISHO_MATH_MAT4_H_
