#include <iostream>
#include <cmath>
#include <array>

// CONSTANTS

constexpr double
        EPSILON = 1E-10,
        PI = 3.14159265358979323846264338327,
        RAD_TO_DEG = 180 / PI,
        DEG_TO_RAD = PI / 180;


template<class T>
class Vec3 {

public:
    T x, y, z;

    Vec3(T x, T y, T z) noexcept : x{x}, y{y}, z{z} {};

    Vec3(const Vec3<T> &v) noexcept : x{v.x}, y{v.y}, z{v.z} {}

    Vec3() noexcept : x{0}, y{0}, z{0} {};
    //Vec3() noexcept = default;

    Vec3<T> plus(const Vec3<T> &v) const {
        return {this->x + v.x, this->y + v.y, this->z + v.z};
    }

    Vec3<T> minus(const Vec3<T> &v) const {
        return {this->x - v.x, this->y - v.y, this->z - v.z};
    }

    Vec3<T> modulo(const Vec3<T> &v) const;

    Vec3<T> times(T s) const {
        return {this->x * s, this->y * s, this->z * s};
    }

    std::string to_string() const {
        return "[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "]";
    }

    bool equals(const Vec3<T> &v, T epsilon) {
        return std::abs(this->x - v.x) < epsilon &&
               std::abs(this->y - v.y) < epsilon &&
               std::abs(this->z - v.z) < epsilon;
    }

};

template
class Vec3<int>;

template
class Vec3<double>;

template<>
Vec3<int> Vec3<int>::modulo(const Vec3<int> &v) const {
    return {this->x % v.x, this->y % v.y, this->z % v.z};
}

template<>
Vec3<double> Vec3<double>::modulo(const Vec3<double> &v) const {
    return {std::fmod(this->x, v.x), std::fmod(this->y, v.y), std::fmod(this->z, v.z)};
}

template<class T>
std::ostream &operator<<(std::ostream &stream, const Vec3<T> &a) {
    return stream << a.to_string();
}

template<class T>
bool operator==(const Vec3<T> &a, const Vec3<T> &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

template<class T>
bool operator!=(const Vec3<T> &a, const Vec3<T> &b) {
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

template<class T>
Vec3<T> operator+(const Vec3<T> &a, const Vec3<T> &b) {
    return a.plus(b);
}

template<class T>
Vec3<T> operator-(const Vec3<T> &a, const Vec3<T> &b) {
    return a.minus(b);
}

template<class T>
Vec3<T> operator%(const Vec3<T> &a, const Vec3<T> &b) {
    return a.modulo(b);
}

template<class T>
Vec3<T> operator*(double scalar, const Vec3<T> &vector) {
    return vector.times(scalar);
}

template<class T>
Vec3<T> operator*(const Vec3<T> &vector, double scalar) {
    return vector.times(scalar);
}

class Matrix3x3d {

private:
    std::array<double, 9> content;

public:

    static Matrix3x3d from_euler_rx(double angle) {
        double s = sin(angle), c = cos(angle);
        return {
                1, 0, 0,
                0, c, -s,
                0, s, c
        };
    }

    static Matrix3x3d from_euler_ry(double angle) {
        double s = sin(angle), c = cos(angle);
        return {
                c, 0, s,
                0, 1, 0,
                -s, 0, c
        };
    }

    static Matrix3x3d from_euler_rz(double angle) {
        double s = sin(angle), c = cos(angle);
        return {
                c, -s, 0,
                s, c, 0,
                0, 0, 1
        };
    }

    static Matrix3x3d from_euler_XYZ(double x, double y, double z);

    static Matrix3x3d from_euler_ZXY(double x, double y, double z);

    static Matrix3x3d from_euler_YZX(double x, double y, double z);

    static Matrix3x3d from_euler_XZY(double x, double y, double z);

    static Matrix3x3d from_euler_YXZ(double x, double y, double z);

    static Matrix3x3d from_euler_ZYX(double x, double y, double z);

    static Matrix3x3d from_euler_XYZ(const Vec3<double> &v) {
        return from_euler_XYZ(v.x, v.y, v.z);
    }

    static Matrix3x3d from_euler_ZXY(const Vec3<double> &v) {
        return from_euler_ZXY(v.x, v.y, v.z);
    }

    static Matrix3x3d from_euler_YZX(const Vec3<double> &v) {
        return from_euler_YZX(v.x, v.y, v.z);
    }

    static Matrix3x3d from_euler_XZY(const Vec3<double> &v) {
        return from_euler_XZY(v.x, v.y, v.z);
    }

    static Matrix3x3d from_euler_YXZ(const Vec3<double> &v) {
        return from_euler_YXZ(v.x, v.y, v.z);
    }

    static Matrix3x3d from_euler_ZYX(const Vec3<double> &v) {
        return from_euler_ZYX(v.x, v.y, v.z);
    }


    Matrix3x3d(double m00, double m01, double m02,
               double m10, double m11, double m12,
               double m20, double m21, double m22) noexcept: content{m00, m01, m02, m10, m11, m12, m20, m21, m22} {}

    explicit Matrix3x3d(std::array<double, 9> content) : content{content} {}

    Matrix3x3d() = default;

    // GETTERS


    double get(int i, int j) const {
        return content[i * 3 + j];
    }

    double get_determinant() const {
        return get(0, 0) * get(1, 1) * get(2, 2) +
               get(0, 1) * get(1, 2) * get(2, 0) +
               get(0, 2) * get(1, 0) * get(2, 1) -
               get(0, 2) * get(1, 1) * get(2, 0) -
               get(0, 0) * get(1, 2) * get(2, 1) -
               get(0, 1) * get(1, 0) * get(2, 2);
    }


    Vec3<double> get_rx_ry_rz_euler_rotation() const {
        double x = atan2(get(1, 2), get(2, 2));
        double cosY = hypot(get(0, 0), get(0, 1));
        double y = atan2(-get(0, 2), cosY);
        double sinX = sin(x);
        double cosX = cos(x);
        double z = atan2(sinX * get(2, 0) - cosX * get(1, 0), cosX * get(1, 1) - sinX * get(2, 1));
        return {-x, -y, -z};
    }


    Vec3<double> get_rx_ry_lz_euler_rotation() const {
        double x = atan2(-get(1, 2), get(2, 2));
        double cosY = hypot(get(0, 0), get(0, 1));
        double y = atan2(get(0, 2), cosY);
        double sinX = sin(x);
        double cosX = cos(x);
        double z = atan2(-cosX * get(1, 0) - sinX * get(2, 0), cosX * get(1, 1) + sinX * get(2, 1));
        return {x, y, z};
    }


    Vec3<double> get_lz_ry_rx_euler_rotation() const {
        double z = atan2(-get(1, 0), get(0, 0));
        double cosY = hypot(get(2, 1), get(2, 2));
        double y = atan2(-get(2, 0), cosY);
        double sinZ = sin(z);
        double cosZ = cos(z);
        double x = atan2(-sinZ * get(0, 2) - cosZ * get(1, 2), sinZ * get(0, 1) + cosZ * get(1, 1));
        return {x, y, z};
    }


    Matrix3x3d times(const Matrix3x3d &m) const {
        std::array<double, 9> result{};

        /* outer loop for acquiring the position (i, j) in the product matrix */
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                const int index = i * 3 + j;

                /* inner loop for calculating the result at (i, j) */
                for (int k = 0, l = 0; k < 3 && l < 3; k++, l++)
                    result[index] += this->get(i, k) * m.get(l, j);
            }

        return Matrix3x3d{result};
    }

    Vec3<double> times(const Vec3<double> &v) const {
        return {
                get(0, 0) * v.x + get(0, 1) * v.y + get(0, 2) * v.z,
                get(1, 0) * v.x + get(1, 1) * v.y + get(1, 2) * v.z,
                get(2, 0) * v.x + get(2, 1) * v.y + get(2, 2) * v.z
        };
    }

    const double &operator[](int i) const {
        return content[i];
    }

    // SETTERS

    double &operator[](int i) {
        return content[i];
    }

    void set(int i, int j, double value) {
        content[i * 3 + j] = value;
    }

    void swap(int i0, int j0, int i1, int j1) {
        const int from = i0 * 3 + j0, to = i1 * 3 + j1;

        double swap = content[to];
        content[to] = content[from];
        content[from] = swap;
    }

    void scale(double factor) {
        for (double &k : content)
            k *= factor;
    }

    // MISC

    std::string to_string() {
        return "[[" + std::to_string(content[0]) +
               ", " + std::to_string(content[1]) +
               ", " + std::to_string(content[2]) + "]," +
               " [" + std::to_string(content[3]) +
               ", " + std::to_string(content[4]) +
               ", " + std::to_string(content[5]) + "]," +
               " [" + std::to_string(content[6]) +
               ", " + std::to_string(content[7]) +
               ", " + std::to_string(content[8]) + "]]";
    }

    /*String toString(DecimalFormat format) {
        StringBuilder
        builder = new StringBuilder("[")
        .append(format.format(content[0]));
        for (int i = 1; i < content.length; i++)
            builder
                    .append(", ")
                    .append(format.format(content[i]));
        return builder.append(']').toString();
    }*/

    bool equals(const Matrix3x3d &other, double epsilon) {
        for (int i = 0; i < 9; i++)
            if (std::abs(this->content[i] - other.content[i]) > epsilon)
                return false;
        return true;
    }

};

// OPERATORS

Vec3<double> operator*(const Matrix3x3d &lhs, const Vec3<double> &rhs) {
    return lhs.times(rhs);
}

Matrix3x3d operator*(const Matrix3x3d &lhs, const Matrix3x3d &rhs) {
    return lhs.times(rhs);
}

// X Y Z

Matrix3x3d Matrix3x3d::from_euler_XYZ(double x, double y, double z) {
    return Matrix3x3d::from_euler_rx(x) * Matrix3x3d::from_euler_ry(y) * Matrix3x3d::from_euler_rz(z);
}

// Z X Y

Matrix3x3d Matrix3x3d::from_euler_ZXY(double x, double y, double z) {
    return Matrix3x3d::from_euler_rz(z) * Matrix3x3d::from_euler_rx(x) * Matrix3x3d::from_euler_ry(y);
}

// Y Z X

Matrix3x3d Matrix3x3d::from_euler_YZX(double x, double y, double z) {
    return Matrix3x3d::from_euler_ry(y) * Matrix3x3d::from_euler_rz(z) * Matrix3x3d::from_euler_rx(x);
}

// X Z Y

Matrix3x3d Matrix3x3d::from_euler_XZY(double x, double y, double z) {
    return Matrix3x3d::from_euler_rx(x) * Matrix3x3d::from_euler_rz(z) * Matrix3x3d::from_euler_ry(y);
}

// Y X Z

Matrix3x3d Matrix3x3d::from_euler_YXZ(double x, double y, double z) {
    return Matrix3x3d::from_euler_ry(y) * Matrix3x3d::from_euler_rx(x) * Matrix3x3d::from_euler_rz(z);
}

// Z Y X

Matrix3x3d Matrix3x3d::from_euler_ZYX(double x, double y, double z) {
    return Matrix3x3d::from_euler_rz(z) * Matrix3x3d::from_euler_ry(y) * Matrix3x3d::from_euler_rx(x);
}

// ROTATION UTILITIES

static const Vec3<double> _360{360, 360, 360};

Vec3<double> craftstudio_rot_to_entity_rot(const Vec3<double> &xyzDegrees) {
    Vec3<double> xyzRad = xyzDegrees * DEG_TO_RAD;
    Matrix3x3d transform = Matrix3x3d(1, 0, 0, 0, 1, 0, 0, 0, -1) * Matrix3x3d::from_euler_YXZ(xyzRad);
    return transform.get_lz_ry_rx_euler_rotation() * RAD_TO_DEG;
}

bool is_zero_rotation(const Vec3<double> &anglesDeg) {
    Vec3<double> transformed = (anglesDeg % _360 + _360) % _360;
    return transformed.x < EPSILON &&
           transformed.y < EPSILON &&
           transformed.z < EPSILON;
}

