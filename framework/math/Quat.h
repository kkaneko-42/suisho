#ifndef SUISHO_MATH_QUAT_H_
#define SUISHO_MATH_QUAT_H_

namespace suisho {

class Vec3;

/**
 * @class Quat
 * @brief Representing a quaternion for 3D rotations and interpolations.
 * @todo Implement
 */
class Quat {
public:
    /**
     * @brief Identity quaternion.
     */
    static Quat kIdentity;

    float x; ///< The x component of the quaternion.
    float y; ///< The y component of the quaternion.
    float z; ///< The z component of the quaternion.
    float w; ///< The w component of the quaternion.

    /**
     * @brief Default constructor. Initializes to identity.
     */
    Quat();

    /**
     * @brief Parameterized constructor.
     * @param xx The x component.
     * @param yy The y component.
     * @param zz The z component.
     * @param ww The w component.
     */
    Quat(float xx, float yy, float zz, float ww);

    /**
     * @brief Copy constructor.
     * @param q The quaternion to copy.
     */
    Quat(const Quat& q);

    /**
     * @brief Move constructor.
     * @param q The quaternion to move.
     */
    Quat(Quat&& q);

    /**
     * @brief Destructor.
     */
    ~Quat();

    /**
     * @brief Copy assignment operator.
     * @param q The quaternion to copy.
     * @return Reference to this quaternion.
     */
    Quat& operator=(const Quat& q);

    /**
     * @brief Move assignment operator.
     * @param q The quaternion to move.
     * @return Reference to this quaternion.
     */
    Quat& operator=(Quat&& q);

    /**
     * @brief Combine this quaternion with another one
     * @param q The quaternion to combine with.
     * @return New Quaternion that rotates in the order of this -> q
     * @todo impl
     */
    Quat operator*(const Quat& q) const;

    /**
     * @brief Combine this quaternion with another one, and assign to this
     * @param q The quaternion to combine with.
     * @return Reference to this quaternion.
     * @todo impl
     */
    Quat& operator*=(const Quat& q);

    /**
     * @brief Rotate the passed 3D vector with this quaternion
     * @param src The vector to be rotated.
     * @return 3D vector after rotation
     * @todo impl
     */
    Vec3 operator*(const Vec3& vec) const;

    /**
     * @brief Checks if this quaternion is equal to another quaternion.
     * @param q The quaternion to compare with.
     * @return True if the quaternions are equal, false otherwise.
     */
    bool operator==(const Quat& q) const;

    /**
     * @brief Creates a quaternion from Euler angles.
     * @param xdeg The x angle in degrees.
     * @param ydeg The y angle in degrees.
     * @param zdeg The z angle in degrees.
     * @return The resulting quaternion.
     * @todo impl
     */
    static Quat fromEuler(float xdeg, float ydeg, float zdeg);

    /**
     * @brief Creates a quaternion from Euler angles.
     * @param euler The vector containing the Euler angles in degrees.
     * @return The resulting quaternion.
     * @todo impl
     */
    static Quat fromEuler(const Vec3& degree);

    /**
     * @brief Creates a quaternion representing a rotation around an axis.
     * @param degree The angle of rotation in degrees.
     * @param axis The axis of rotation.
     * @return The resulting quaternion.
     * @todo impl
     */
    static Quat angleAxis(float degree, const Vec3& axis);

    /**
     * @brief Linearly interpolates between two quaternions.
     * @param a The start quaternion.
     * @param b The end quaternion.
     * @param t The interpolation factor ranged [0, 1].
     * @return The interpolated quaternion.
     * @todo impl
     */
    static Quat lerp(const Quat& a, const Quat& b, float t);

    /**
     * @brief Spherically interpolates between two quaternions.
     * @param a The start quaternion.
     * @param b The end quaternion.
     * @param t The interpolation factor ranged [0, 1].
     * @return The interpolated quaternion.
     * @todo impl
     */
    static Quat slerp(const Quat& a, const Quat& b, float t);
};

}; // namespace suisho

#endif
