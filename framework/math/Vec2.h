#ifndef SUISHO_MATH_VEC2_H_
#define SUISHO_MATH_VEC2_H_

namespace suisho {

/**
 * @brief 4-dimentional vector
 */
class Vec2 {
public:
    /// @brief (0, 0)
    static const Vec2 kZero;

    /// @brief (1, 1)
    static const Vec2 kOne;

        /// @brief Right-pointing unit vector. In this engine, equals to (1, 0)
    static const Vec2 kRight;

    /// @brief Left-pointing unit vector. In this engine, equals to (-1, 0)
    static const Vec2 kLeft;

    /// @brief Up-pointing unit vector. In this engine, equals to (0, 1)
    static const Vec2 kUp;

    /// @brief Down-pointing unit vector. In this engine, equals to (0, -1)
    static const Vec2 kDown;

    /// @brief x coord
    float x;

    /// @brief y coord
    float y;

    /// @brief Creates a new vector initialized to all zeros
    Vec2();

    /// @brief Creates a new vector initialized to the specified values
    /// @param xval x coord
    /// @param yval y coord
    Vec2(float xval, float yval);

    /// @brief Copy the all elements of src
    /// @param src copy source
    Vec2(const Vec2& src);

    /// @brief Move the all elements of src
    /// @param src move source
    Vec2(Vec2&& src) noexcept;

    /// @brief Destructor
    ~Vec2();

    /// @brief Copy the all elements of src
    /// @param rhs copy src
    /// @return *this after the copy
    Vec2& operator=(const Vec2& rhs);

    /// @brief Move the all elements of src
    /// @param rhs move src
    /// @return *this after the move
    Vec2& operator=(Vec2&& rhs) noexcept;

    /// @param rhs compare target
    /// @return True if this->t == rhs. t for any element t. False otherwise
    bool operator==(const Vec2& rhs) const;

    /// @return Vector adding each element
    Vec2 operator+(const Vec2& rhs) const;

    /// @brief Adds rhs to this
    /// @return Reference to this after the addition
    Vec2& operator+=(const Vec2& rhs);

    /// @return Vector subtracting each element
    Vec2 operator-(const Vec2& rhs) const;

    /// @brief Subs rhs to this
    /// @return Reference to this after the substraction
    Vec2& operator-=(const Vec2& rhs);

    /// @return Vector multiplying s to each element of this
    Vec2 operator*(float s) const;

    /// @return Vector multiplying s to each element of this
    Vec2& operator*=(float s);

    /// @return Vector dividing s to each element of this
    inline Vec2 operator/(float s) const;

    /// @brief Divs s to this
    /// @return Reference to this after the division
    inline Vec2& operator/=(float s);

    /// @return Length of this vector
    float length() const;

    /// @return Squared length of this vector
    float lengthSqr() const;

    /// @brief Set the length to 1
    void normalize();

    /// @return Vector applied normalize()
    Vec2 normalized() const;

    /// @return Inner product of this and rhs
    float dot(const Vec2& rhs) const;
};

/// @return Vector multiplying s to each element of this
inline Vec2 operator*(float s, const Vec2& v) { return v * s; }

} // namespace suisho

#endif // SUISHO_MATH_VEC2_H_
