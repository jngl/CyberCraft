//
// Created by jngl on 28/04/2020.
//

#ifndef CYBERCRAFT_MATH_H
#define CYBERCRAFT_MATH_H

#include <cmath>
#include <array>

namespace cc{
    template<class T>
    bool equal(T a, T b, T precision = static_cast<T>(0.0001)){
        return a-precision<b && b<a+precision;
    }

    template<class T>
    T mix(T x, T y, T a) { return x * (1 - a) + y * a; }

    template<class T>
    T fractionalPart(T v) {
        T tmp;
        return std::modf(v, &tmp);
    }

    template<class T>
    T sign(T v) {
        return v < static_cast<T>(0.f) ? -1.0f : 1.0f;
    }

    using std::floor;
    using std::cos;
    using std::sin;
    using std::tan;
    using std::max;
    using std::min;
    using std::abs;
    using std::sqrt;

    template<class T>
    struct Vector2 {
        T x = 0;
        T y = 0;

        constexpr Vector2<T> operator-(const Vector2<T> &b) const {
            return Vector2<T>{x - b.x, y - b.y};
        }

        constexpr Vector2<T> operator-(const T &b) const { return Vector2<T>{x - b, y - b}; }

        constexpr Vector2<T> operator-() const {
            return Vector2<T>{
                    -x, -y,
            };
        }

        constexpr Vector2<T> operator+(const Vector2<T> &b) const {
            return Vector2<T>{x + b.x, y + b.y};
        }

        constexpr Vector2<T> operator*(T scale) const {
            return Vector2<T>{x * scale, y * scale};
        }

        constexpr Vector2<T> operator/(T scale) const {
            return Vector2<T>{x / scale, y / scale};
        }

        constexpr Vector2<T> operator*(const Vector2<T> &right) const {
            return Vector2<T>{x * right.x, y * right.y};
        }

        constexpr Vector2<T> operator/(const Vector2<T> &right) const {
            return Vector2<T>{x / right.x, y / right.y};
        }

        constexpr Vector2<T> &operator+=(const Vector2<T> &right) const {
            x += right.x;
            y += right.y;
            return *this;
        }

        constexpr Vector2<T> &operator-=(const Vector2<T> &right) {
            x -= right.x;
            y -= right.y;
            return *this;
        }

        constexpr Vector2<T> &operator*=(const Vector2<T> &right) {
            x *= right.x;
            y *= right.y;
            return *this;
        }

        constexpr Vector2<T> &operator/=(const Vector2<T> &right) {
            x /= right.x;
            y /= right.y;
            return *this;
        }

        constexpr T getDotProduct(const Vector2<T> &t) const { return x * t.x + y * t.y; }

        constexpr bool isInRect(T minX, T maxX, T minY, T maxY){
            return minX <= x && x <=maxX && minY <= x && x <= maxY;
        }

        template<class T2>
        constexpr Vector2<T2> toVector(){
            return Vector2<T2>{static_cast<T2>(x), static_cast<T2>(y)};
        }

        constexpr void set(T p_x, T p_y){
            x = p_x;
            y = p_y;
        }
    };

    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;
    typedef Vector2<unsigned int> Vector2ui;

    template<class T>
    struct Vector3 {
        T x = 0;
        T y = 0;
        T z = 0;

        constexpr Vector3<T> operator-(const Vector3<T> &b) const {
            return Vector3<T>{x - b.x, y - b.y, z - b.z};
        }

        constexpr Vector3<T> operator-() const { return Vector3<T>{-x, -y, -z}; }

        constexpr Vector3<T> operator+(const Vector3<T> &b) const {
            return Vector3<T>{x + b.x, y + b.y, z + b.z};
        }

        constexpr Vector3<T> operator*(const T scale) {
            return Vector3<T>{x * scale, y * scale, z * scale};
        }

        constexpr Vector3<T> operator/(const T scale) {
            return Vector3<T>{x / scale, y / scale, z / scale};
        }

        constexpr Vector3<T> operator*(const Vector3<T> &right) {
            return Vector3<T>{x * right.x, y * right.y, z * right.z};
        }

        constexpr Vector3<T> operator/(const Vector3<T> &right) {
            return Vector3<T>{x / right.x, y / right.y, z / right.z};
        }

        constexpr Vector3<T> &operator+=(const Vector3<T> &right) {
            x += right.x;
            y += right.y;
            z += right.z;
            return *this;
        }

        constexpr Vector3<T> &operator-=(const Vector3<T> &right) {
            x -= right.x;
            y -= right.y;
            z -= right.z;
            return *this;
        }

        constexpr Vector3<T> &operator*=(const Vector3<T> &right) {
            x *= right.x;
            y *= right.y;
            z *= right.z;
            return *this;
        }

        constexpr Vector3<T> &operator*=(const T &right) {
            x *= right;
            y *= right;
            z *= right;
            return *this;
        }

        constexpr Vector3<T> &operator/=(const Vector3<T> &right) {
            x /= right.x;
            y /= right.y;
            z /= right.z;
            return *this;
        }

        constexpr bool operator==(const Vector3<T> &right) {
            return x == right.x && y == right.y && z == right.z;
        }

        constexpr  void set(T px, T py, T pz) {
            x = px;
            y = py;
            z = pz;
        }

        constexpr void setAllAxes(T v) {
            x = v;
            y = v;
            z = v;
        }

        constexpr T getLengthSquared() const { return x * x + y * y + z * z; }

        constexpr T getLength() const { return sqrtf(x * x + y * y + z * z); }

        constexpr Vector3<T> &normalize() {
            T length = getLength();

            if (length == 0) {
                set(0, 0, 0);
                return *this;
            }
            x /= length;
            y /= length;
            z /= length;
            return *this;
        }

        constexpr T getDotProduct(const Vector3<T> &t) const {
            return x * t.x + y * t.y + z * t.z;
        }

        constexpr Vector3<T> getCrossProduct(const Vector3<T> &v) const {
            return {y * v.z - z * v.y, v.x * z - v.z * x, x * v.y - y * v.x};
        }

        constexpr Vector3<T> getFloor() { return Vector3<T>{floor(x), floor(y), floor(z)}; }

        constexpr Vector3<T> getSign() { return Vector3<T>{sign(x), sign(y), sign(z)}; }
    };

    typedef Vector3<float> Vector3f;
    typedef Vector3<int> Vector3i;

    template<class T>
    struct Vector4 {
        T x = 0;
        T y = 0;
        T z = 0;
        T w = 0;
    };

    typedef Vector4<float> Vector4f;
    typedef Vector4<int> Vector4i;

    template<class T>
    struct Matrix4 {
        constexpr Matrix4() {
            setIdentity();
        }

        constexpr void setIdentity() {
            for(auto& line : m){
                for(T& number : line) {
                    number = 0;
                }
            }

            m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
        }

        constexpr Matrix4<T> operator*(const Matrix4<T> &t) const {
            Matrix4<T> r;
            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++) {
                    r.m[i][j] = m[0][j] * t.m[i][0] + m[1][j] * t.m[i][1] +
                                m[2][j] * t.m[i][2] + m[3][j] * t.m[i][3];
                }
            }
            return r;
        }

        constexpr Matrix4<T> operator*=(const Matrix4<T> &t) {
            *this = (*this) * t;
            return *this;
        }

        constexpr void projectOrthographic(T left, T right, T bottom, T top,
                                 T pNear, T pFar) {
            setIdentity();

            T XD = right - left;
            T YD = top - bottom;
            T ZD = pFar - pNear;

            m[0][0] = 2.0f / XD;
            m[1][1] = 2.0f / YD;
            m[2][2] = -2.0f / ZD;

            m[3][0] = -(right + left) / XD;
            m[3][1] = -(top + bottom) / YD;
            m[3][2] = -(pFar + pNear) / ZD;
        }

        constexpr void projectPerspective(T pFOV, T pAspectRatio, T pNear, T pFar) {
            constexpr T fullTurn = 360;
            T tanThetaOver2 = static_cast<T>(tan(pFOV * (static_cast<T>(M_PI) / fullTurn)));
            setIdentity();

            // X and Y scaling
            m[0][0] = 1 / tanThetaOver2;
            m[1][1] = pAspectRatio / tanThetaOver2;

            // Z coordinate makes z -1 when we're on the near plane and +1 on the far
            // plane
            m[2][2] = (pNear + pFar) / (pNear - pFar);
            m[3][2] = 2 * pNear * pFar / (pNear - pFar);

            // W = -1 so that we have [x y z -z], a homogenous vector that becomes [-x/z
            // -y/z -1] after division by w.
            m[2][3] = -1;

            // Must zero this out, the identity has it as 1.
            m[3][3] = 0;
        }

        constexpr void setTranslation(const Vector3<T> &vecPos) {
            setIdentity();
            m[3][0] = vecPos.x;
            m[3][1] = vecPos.y;
            m[3][2] = vecPos.z;
        }

        constexpr void addTranslation(const Vector3<T> &v) {
            Matrix4<T> r;
            r.setTranslation(v);
            (*this) *= r;
        }

        constexpr void addTranslation(T x, T y, T z) { addTranslation({x, y, z}); }

        constexpr void setScale(const Vector3<T> &vecScale) {
            setIdentity();
            m[0][0] = vecScale.x;
            m[1][1] = vecScale.y;
            m[2][2] = vecScale.z;
        }

        constexpr void addScale(const Vector3<T> &vecScale) {
            Matrix4<T> r;
            r.setScale(vecScale);
            (*this) *= r;
        }

        constexpr void addScale(T x, T y, T z) {
            addScale(Vector3<T>{x, y, z});
        }

        constexpr void setRotation(T flAngle, const Vector3<T> &v) {
            setIdentity();
            T x = v.x;
            T y = v.y;
            T z = v.z;

            T c = cos(flAngle);
            T s = sin(flAngle);
            T t = 1 - c;

            m[0][0] = x * x * t + c;
            m[1][0] = x * y * t - z * s;
            m[2][0] = x * z * t + y * s;

            m[0][1] = y * x * t + z * s;
            m[1][1] = y * y * t + c;
            m[2][1] = y * z * t - x * s;

            m[0][2] = z * x * t - y * s;
            m[1][2] = z * y * t + x * s;
            m[2][2] = z * z * t + c;
        }

        constexpr void addRotation(float flAngle, const Vector3<T> &v) {
            Matrix4<T> r;
            r.setRotation(flAngle, v);
            (*this) *= r;
        }

        constexpr void lookAt(Vector3<T> const &eye, Vector3<T> const &center,
                    Vector3<T> const &up) {
            Vector3<T> f = center - eye;
            f.normalize();

            Vector3<T> u = up;
            u.normalize();

            Vector3<T> s = f.getCrossProduct(u);
            s.normalize();
            u = s.getCrossProduct(f);

            m[0][0] = s.x;
            m[0][1] = u.x;
            m[0][2] = -f.x;
            m[0][3] = 0.f;
            m[1][0] = s.y;
            m[1][1] = u.y;
            m[1][2] = -f.y;
            m[1][3] = 0.f;
            m[2][0] = s.z;
            m[2][1] = u.z;
            m[2][2] = -f.z;
            m[2][3] = 0.f;
            m[3][0] = -s.getDotProduct(eye);
            m[3][1] = -u.getDotProduct(eye);
            m[3][2] = f.getDotProduct(eye);
            m[3][3] = 1.f;
        }

        std::array<std::array<T, 4>, 4> m;
    };

    typedef Matrix4<float> Matrix4f;
}

#endif //CYBERCRAFT_CONVERSION_H
