#ifndef SUISHO_MATH_VEC4_H_
#define SUISHO_MATH_VEC4_H_

namespace suisho {

/**
 * @brief 4-dimentional vector
 */
class Vec4 {
public:
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
    /// @return *this
    Vec4& operator=(const Vec4& rhs);

    /// @brief Move the all elements of src
    /// @param rhs move src
    /// @return *this
    Vec4& operator=(Vec4&& rhs) noexcept;

    /// @param rhs compare target
    /// @return True if this->t == rhs. t for any element t. False otherwise
    bool operator==(const Vec4& rhs) const;
};

} // namespace suisho

#endif // SUISHO_MATH_VEC4_H_
