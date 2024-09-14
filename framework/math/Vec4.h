#ifndef SUISHO_MATH_VEC4_H_
#define SUISHO_MATH_VEC4_H_

namespace suisho {

/**
 * @brief 4-dimentional vector
 */
class Vec4 {
public:
    /// @brief (0, 0, 0, 0)
    static const Vec4 kZero;

    /// @brief (1, 1, 1, 1)
    static const Vec4 kOne;

    /// @brief x coord
    float x;

    /// @brief y coord
    float y;

    /// @brief z coord
    float z;

    /// @brief w coord
    float w;

    /// @brief Creates a new vector initialized to all zeros
    Vec4();

    /// @brief Creates a new vector initialized to the specified values
    /// @param xval x coord
    /// @param yval y coord
    /// @param zval z coord
    /// @param wval w coord
    Vec4(float xval, float yval, float zval, float wval);

    /// @brief Copy the all elements of src
    /// @param src copy source
    Vec4(const Vec4& src);

    /// @brief Move the all elements of src
    /// @param src move source
    Vec4(Vec4&& src) noexcept;

    /// @brief Destructor
    ~Vec4();

    /// @brief Copy the all elements of src
    /// @param rhs copy src
    /// @return *this after the copy
    Vec4& operator=(const Vec4& rhs);

    /// @brief Move the all elements of src
    /// @param rhs move src
    /// @return *this after the move
    Vec4& operator=(Vec4&& rhs) noexcept;

    /// @param rhs compare target
    /// @return True if this->t == rhs. t for any element t. False otherwise
    bool operator==(const Vec4& rhs) const;

    /// @return Vector adding each element
    Vec4 operator+(const Vec4& rhs) const;

    /// @brief Adds rhs to this
    /// @return Reference to this after the addition
    Vec4& operator+=(const Vec4& rhs);

    /// @return Vector subtracting each element
    Vec4 operator-(const Vec4& rhs) const;

    /// @brief Subs rhs to this
    /// @return Reference to this after the substraction
    Vec4& operator-=(const Vec4& rhs);

    /// @return Vector multiplying s to each element of this
    Vec4 operator*(float s) const;

    /// @return Vector multiplying s to each element of this
    Vec4& operator*=(float s);

    /// @return Vector dividing s to each element of this
    inline Vec4 operator/(float s) const;

    /// @brief Divs s to this
    /// @return Reference to this after the division
    inline Vec4& operator/=(float s);

    /// @return Length of this vector
    float length() const;

    /// @return Squared length of this vector
    float lengthSqr() const;

    /// @brief Set the length to 1
    void normalize();

    /// @return Vector applied normalize()
    Vec4 normalized() const;

    /// @return Inner product of this and rhs
    float dot(const Vec4& rhs) const;
};

/// @return Vector multiplying s to each element of this
inline Vec4 operator*(float s, const Vec4& v) { return v * s; }

} // namespace suisho

#endif // SUISHO_MATH_VEC4_H_
