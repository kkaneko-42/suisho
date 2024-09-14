#ifndef SUISHO_MATH_VEC3_H_
#define SUISHO_MATH_VEC3_H_

namespace suisho {

/**
 * @brief 3-dimentional vector
 */
class Vec3 {
public:
    /// @brief (0, 0, 0, 0)
    static const Vec3 kZero;

    /// @brief (1, 1, 1, 1)
    static const Vec3 kOne;

    /// @brief x coord
    float x;

    /// @brief y coord
    float y;

    /// @brief z coord
    float z;

    /// @brief Creates a new vector initialized to all zeros
    Vec3();

    /// @brief Creates a new vector initialized to the specified values
    /// @param xval x coord
    /// @param yval y coord
    /// @param zval z coord
    Vec3(float xval, float yval, float zval);

    /// @brief Copy the all elements of src
    /// @param src copy source
    Vec3(const Vec3& src);

    /// @brief Move the all elements of src
    /// @param src move source
    Vec3(Vec3&& src) noexcept;

    /// @brief Destructor
    ~Vec3();

    /// @brief Copy the all elements of src
    /// @param rhs copy src
    /// @return *this after the copy
    Vec3& operator=(const Vec3& rhs);

    /// @brief Move the all elements of src
    /// @param rhs move src
    /// @return *this after the move
    Vec3& operator=(Vec3&& rhs) noexcept;

    /// @param rhs compare target
    /// @return True if this->t == rhs. t for any element t. False otherwise
    bool operator==(const Vec3& rhs) const;

    /// @return Vector adding each element
    Vec3 operator+(const Vec3& rhs) const;

    /// @brief Adds rhs to this
    /// @return Reference to this after the addition
    Vec3& operator+=(const Vec3& rhs);

    /// @return Vector subtracting each element
    Vec3 operator-(const Vec3& rhs) const;

    /// @brief Subs rhs to this
    /// @return Reference to this after the substraction
    Vec3& operator-=(const Vec3& rhs);

    /// @return Vector multiplying s to each element of this
    Vec3 operator*(float s) const;

    /// @return Vector multiplying s to each element of this
    Vec3& operator*=(float s);

    /// @return Vector dividing s to each element of this
    inline Vec3 operator/(float s) const;

    /// @brief Divs s to this
    /// @return Reference to this after the division
    inline Vec3& operator/=(float s);

    /// @return Length of this vector
    float length() const;

    /// @return Squared length of this vector
    float lengthSqr() const;

    /// @brief Set the length to 1
    void normalize();

    /// @return Vector applied normalize()
    Vec3 normalized() const;

    /// @return Inner product of this and rhs
    float dot(const Vec3& rhs) const;
};

/// @return Vector multiplying s to each element of this
inline Vec3 operator*(float s, const Vec3& v) { return v * s; }


} // namespace suisho

#endif // SUISHO_MATH_VEC3_H_
