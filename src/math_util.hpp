//
// Created by user on 4/13/19.
//

#ifndef CRAFTSTUDIO2ENTITY_CPP_MATH_UTIL_HPP
#define CRAFTSTUDIO2ENTITY_CPP_MATH_UTIL_HPP

#include <iostream>
#include <math.h>

struct Vec2i {
    int x;
    int y;
};

template<class T>
class Vec3 {

public:
    T x, y, z;

    Vec3(T x, T y, T z) noexcept;

    Vec3(const Vec3<T> &v) noexcept;

    Vec3() noexcept;

    ~Vec3() {

    }

    Vec3<T> plus(const Vec3<T> &v) const;

    Vec3<T> minus(const Vec3<T> &v) const;

    Vec3<T> modulo(const Vec3<T> &v) const;

    Vec3<T> times(T s) const;

    std::string to_string() const;

    bool equals(const Vec3<T> &v, T epsilon);
};

template<class T>
std::ostream &operator<<(std::ostream &stream, const Vec3<T> &a);

template<class T>
bool operator==(const Vec3<T> &a, const Vec3<T> &b);

template<class T>
bool operator!=(const Vec3<T> &a, const Vec3<T> &b);

template<class T>
Vec3<T> operator+(const Vec3<T> &a, const Vec3<T> &b);

template<class T>
Vec3<T> operator-(const Vec3<T> &a, const Vec3<T> &b);

template<class T>
Vec3<T> operator%(const Vec3<T> &a, const Vec3<T> &b);

template<class T>
Vec3<T> operator*(double scalar, const Vec3<T> &vector);

template<class T>
Vec3<T> operator*(const Vec3<T> &vector, double scalar);

class Matrix3x3d {

private:
    double content[9];

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

    Matrix3x3d(const double content...) noexcept : content{content} {}

#pragma clang diagnostic pop


public:

    /**
     * <p>
     * Returns a 3x3 rotation matrix representing a counter-clockwise rotation around the x-axis.
     * </p>
     * <p>
     * For easier understanding, see: <a href="https://en.wikipedia.org/wiki/Right-hand_rule">Right Hand Rule</a>.
     * </p>
     *
     * @param angle the angle in radians
     * @return a new rotation matrix
     */
    static Matrix3x3d from_euler_rx(double angle);

    /**
     * <p>
     * Returns a 3x3 rotation matrix representing a counter-clockwise rotation around the y-axis.
     * </p>
     * <p>
     * For easier understanding, see: <a href="https://en.wikipedia.org/wiki/Right-hand_rule">Right Hand Rule</a>.
     * </p>
     *
     * @param angle the angle in radians
     * @return a new rotation matrix
     */
    static Matrix3x3d from_euler_ry(double angle);

    /**
     * <p>
     * Returns a 3x3 rotation matrix representing a counter-clockwise rotation around the z-axis.
     * </p>
     * <p>
     * For easier understanding, see: <a href="https://en.wikipedia.org/wiki/Right-hand_rule">Right Hand Rule</a>.
     * </p>
     *
     * @param angle the angle in radians
     * @return a new rotation matrix
     */
    static Matrix3x3d from_euler_rz(double angle);

    static Matrix3x3d from_euler_XYZ(double x, double y, double z);

    static Matrix3x3d from_euler_ZXY(double x, double y, double z);

    static Matrix3x3d from_euler_YZX(double x, double y, double z);

    static Matrix3x3d from_euler_XZY(double x, double y, double z);

    static Matrix3x3d from_euler_YXZ(double x, double y, double z);

    static Matrix3x3d from_euler_ZYX(double x, double y, double z);

    static Matrix3x3d from_euler_XYZ(const Vec3<double> &v);

    static Matrix3x3d from_euler_ZXY(const Vec3<double> &v);

    static Matrix3x3d from_euler_YZX(const Vec3<double> &v);

    static Matrix3x3d from_euler_XZY(const Vec3<double> &v);

    static Matrix3x3d from_euler_YXZ(const Vec3<double> &v);

    static Matrix3x3d from_euler_ZYX(const Vec3<double> &v);


    Matrix3x3d(double m00, double m01, double m02,
               double m10, double m11, double m12,
               double m20, double m21, double m22) noexcept;

    Matrix3x3d() = default;

    // GETTERS


    double get(int i, int j) const;

    /**
     * Special case formula for 3x3 matrices. (Using <a href="https://en.wikipedia.org/wiki/Cramer%27s_rule">Cramer's
     * Rule</a>)
     *
     * @return the determinant of the matrix
     */
    double get_determinant() const;


    Vec3<double> get_rx_ry_rz_euler_rotation() const;


    Vec3<double> get_rx_ry_lz_euler_rotation() const;


    Vec3<double> get_lz_ry_rx_euler_rotation() const;

    /**
     * Multiplies this matrix with another matrix which will be the right hand side of the matrix multiplication.
     *
     * @param m the right hand side matrix
     */
    Matrix3x3d times(const Matrix3x3d &m) const;

    Vec3<double> times(const Vec3<double> &v) const;

    const double &operator[](int i) const;

    // SETTERS

    double &operator[](int i);

    void set(int i, int j, double value);

    void swap(int i0, int j0, int i1, int j1);

    void scale(double factor);

    // MISC

    std::string to_string();

    bool equals(const Matrix3x3d &other, double epsilon);

};

// OPERATORS

Vec3<double> operator*(const Matrix3x3d &lhs, const Vec3<double> &rhs);

Matrix3x3d operator*(const Matrix3x3d &lhs, const Matrix3x3d &rhs);

// ROTATION UTILITIES

static const Vec3<double> _360 = Vec3<double>(360, 360, 360);

Vec3<double> craftstudio_rot_to_entity_rot(const Vec3<double> &xyzDegrees);

bool is_zero_rotation(const Vec3<double> &anglesDeg);

#endif //CRAFTSTUDIO2ENTITY_CPP_MATH_UTIL_HPP
