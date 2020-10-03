#pragma once

#include <algorithm>
#include <cmath>
#include <cstring>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

namespace math {
  template <class T> T mix(T x, T y, T a) { return x * (1 - a) + y * a; }

  template <class T> T fract(T v) {
    T intpart;
    return std::modf(v, &intpart);
  }

  template <class T> T sign(T v) {
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

  template <class T> struct Vector2 {
    T x, y;

    Vector2() : x(0.f), y(0.f) {}

    Vector2(T px, T py) : x(px), y(py) {}

    Vector2<T> operator-(const Vector2<T> &b) const {
      return Vector2<T>{x - b.x, y - b.y};
    }

    Vector2<T> operator-(const T &b) const { return Vector2<T>{x - b, y - b}; }

    Vector2<T> operator-() const {
      return Vector2<T>{
        -x, -y,
	  };
    }

    Vector2<T> operator+(const Vector2<T> &b) const {
      return Vector2<T>{x + b.x, y + b.y};
    }

    Vector2<T> operator*(const T scale) {
      return Vector2<T>{x * scale, y * scale};
    }

    Vector2<T> operator/(const T scale) {
      return Vector2<T>{x / scale, y / scale};
    }

    Vector2<T> operator*(const Vector2<T> &right) {
      return Vector2<T>{x * right.x, y * right.y};
    }

    Vector2<T> operator/(const Vector2<T> &right) {
      return Vector2<T>{x / right.x, y / right.y};
    }

    Vector2<T> &operator+=(const Vector2<T> &right) {
      x += right.x;
      y += right.y;
      return *this;
    }

    Vector2<T> &operator-=(const Vector2<T> &right) {
      x -= right.x;
      y -= right.y;
      return *this;
    }

    Vector2<T> &operator*=(const Vector2<T> &right) {
      x *= right.x;
      y *= right.y;
      return *this;
    }

    Vector2<T> &operator/=(const Vector2<T> &right) {
      x /= right.x;
      y /= right.y;
      return *this;
    }

    T getDotProduct(const Vector2<T> &t) const { return x * t.x + y * t.y; }
  };

  typedef Vector2<float> Vector2f;
  typedef Vector2<int> Vector2i;

  template <class T> struct Vector3 {
    T x, y, z;

    Vector3() : x(0.f), y(0.f), z(0.f) {}

    Vector3(T px, T py, T pz) : x(px), y(py), z(pz) {}

    Vector3<T> operator-(const Vector3<T> &b) const {
      return Vector3<T>{x - b.x, y - b.y, z - b.z};
    }

    Vector3<T> operator-() const { return Vector3<T>{-x, -y, -z}; }

    Vector3<T> operator+(const Vector3<T> &b) const {
      return Vector3<T>{x + b.x, y + b.y, z + b.z};
    }

    Vector3<T> operator*(const T scale) {
      return Vector3<T>{x * scale, y * scale, z * scale};
    }

    Vector3<T> operator/(const T scale) {
      return Vector3<T>{x / scale, y / scale, z / scale};
    }

    Vector3<T> operator*(const Vector3<T> &right) {
      return Vector3<T>{x * right.x, y * right.y, z * right.z};
    }

    Vector3<T> operator/(const Vector3<T> &right) {
      return Vector3<T>{x / right.x, y / right.y, z / right.z};
    }

    Vector3<T> &operator+=(const Vector3<T> &right) {
      x += right.x;
      y += right.y;
      z += right.z;
      return *this;
    }

    Vector3<T> &operator-=(const Vector3<T> &right) {
      x -= right.x;
      y -= right.y;
      z -= right.z;
      return *this;
    }

    Vector3<T> &operator*=(const Vector3<T> &right) {
      x *= right.x;
      y *= right.y;
      z *= right.z;
      return *this;
    }

    Vector3<T> &operator*=(const T &right) {
      x *= right;
      y *= right;
      z *= right;
      return *this;
    }

    Vector3<T> &operator/=(const Vector3<T> &right) {
      x /= right.x;
      y /= right.y;
      z /= right.z;
      return *this;
    }

    bool operator==(const Vector3<T> &right){
      return x==right.x && y==right.y && z==right.z;
    }

    void set(T px, T py, T pz) {
      x = px;
      y = py;
      z = pz;
    }

    void setAllAxes(T v) {
      x = v;
      y = v;
      z = v;
    }

    T getLengthSquared() const { return x * x + y * y + z * z; }
    T getLength() const { return sqrtf(x * x + y * y + z * z); }

    Vector3<T> &normalize() {
      T length = getLength();

      if (!length) {
	set(0, 0, 0);
	return *this;
      }
      x /= length;
      y /= length;
      z /= length;
      return *this;
    }

    T getDotProduct(const Vector3<T> &t) const {
      return x * t.x + y * t.y + z * t.z;
    }

    Vector3<T> getCrossProduct(const Vector3<T> &v) const {
      return {y * v.z - z * v.y, v.x * z - v.z * x, x * v.y - y * v.x};
    }

    Vector3<T> getFloor() { return Vector3<T>{floor(x), floor(y), floor(z)}; }

    Vector3<T> getSign() { return Vector3<T>{sign(x), sign(y), sign(z)}; }

  /*  static Vector3<T> max(Vector3<T> a, Vector3<T> b) {
      return Vector3<T>{a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y,
	  a.z > b.z ? a.z : b.z};
    }

    static Vector3<T> mix(Vector3<T> a, Vector3<T> b, T v) {
      return Vector3<T>{math::mix(a.x, b.x, v), math::mix(a.y, b.y, v),
	  math::mix(a.z, b.z, v)};
    }*/
  };

  typedef Vector3<float> Vector3f;
  typedef Vector3<int> Vector3i;

  template <class T> struct Vector4 {
    T x, y, z, w;

    Vector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}

    Vector4(T px, T py, T pz, T pw) : x(px), y(py), z(pz), w(pw) {}
  };

  typedef Vector4<float> Vector4f;
  typedef Vector4<int> Vector4i;

  template <class T> struct Matrix4 {
    Matrix4(){
      setIdentity();
    }
    
    void setIdentity() {
      memset(this, 0, sizeof(Matrix4<T>));

      m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    }

    Matrix4<T> operator*(const Matrix4<T> &t) const {
      Matrix4<T> r;
      for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	  r.m[i][j] = m[0][j] * t.m[i][0] + m[1][j] * t.m[i][1] +
	    m[2][j] * t.m[i][2] + m[3][j] * t.m[i][3];
	}
      }
      return r;
    }

    Matrix4<T> operator*=(const Matrix4<T> &t) {
      *this = (*this) * t;
      return *this;
    }

    void projectOrthographic(float left, float right, float bottom, float top,
			     float pNear, float pFar) {
      setIdentity();

      float XD = right - left;
      float YD = top - bottom;
      float ZD = pFar - pNear;

      m[0][0] = 2.0f / XD;
      m[1][1] = 2.0f / YD;
      m[2][2] = -2.0f / ZD;

      m[3][0] = -(right + left) / XD;
      m[3][1] = -(top + bottom) / YD;
      m[3][2] = -(pFar + pNear) / ZD;
    }

    void projectPerspective(float pFOV, float pAspectRatio, float pNear, float pFar) {
      float tanThetaOver2 = static_cast<float>(tan(pFOV * (M_PI / 360.0)));
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

    void setTranslation(const Vector3<T> &vecPos) {
      setIdentity();
      m[3][0] = vecPos.x;
      m[3][1] = vecPos.y;
      m[3][2] = vecPos.z;
    }

    void addTranslation(const Vector3<T> &v) {
      Matrix4<T> r;
      r.setTranslation(v);
      (*this) *= r;
    }

    void addTranslation(T x, T y, T z) { addTranslation({x, y, z}); }

    void setScale(const Vector3<T> &vecScale) {
      setIdentity();
      m[0][0] = vecScale.x;
      m[1][1] = vecScale.y;
      m[2][2] = vecScale.z;
    }

    void addScale(const Vector3<T> &vecScale) {
      Matrix4<T> r;
      r.setScale(vecScale);
      (*this) *= r;
    }

    void addScale(T x, T y, T z){
      addScale(Vector3<T>(x, y, z));
    }

    void setRotation(float flAngle, const Vector3<T> &v) {
      setIdentity();
      float x = v.x;
      float y = v.y;
      float z = v.z;

      float c = cos(flAngle);
      float s = sin(flAngle);
      float t = 1 - c;

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

    void addRotation(float flAngle, const Vector3<T> &v) {
      Matrix4<T> r;
      r.setRotation(flAngle, v);
      (*this) *= r;
    }

    void lookAt(Vector3<T> const &eye, Vector3<T> const &center,
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

    T m[4][4];
  };

  typedef Matrix4<float> Matrix4f;
}
