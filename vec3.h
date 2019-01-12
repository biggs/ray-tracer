#include <math.h>
#include <stdlib.h>
#include <iostream>


class vec3 {
public:
  vec3() {}
  vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

  inline float x() const { return e[0]; }
  inline float y() const { return e[1]; }
  inline float z() const { return e[2]; }
  inline float r() const { return e[0]; }
  inline float b() const { return e[1]; }
  inline float g() const { return e[2]; }

  inline const vec3& operator+() const { return *this; }
  inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  inline float operator[](int i) const { return e[i]; }
  inline float& operator[](int i) { return e[i]; }

  inline vec3& operator+=(const vec3 &v2);
  inline vec3& operator-=(const vec3 &v2);
  inline vec3& operator*=(const vec3 &v2);
  inline vec3& operator*=(const float t);
  inline vec3& operator/=(const vec3 &v2);
  inline vec3& operator/=(const float t);

  inline float length() const {
    return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }

  inline int* as_ppm() const {
    int* out = new int[3];
    for (int i = 0; i < 3; i++) {
      out[i] = int(255.99*e[i]);
    }
    return out;
  }

  float e[3];
  };

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
	return vec3(v1[0] * v2[0],v1[1] * v2[1], v1[2] * v2[2]);
}

inline vec3 operator*(float t, const vec3 &v) {
  return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator/(float t, const vec3 &v) {
  return vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

inline vec3 unit_vector(const vec3 &v) {
  float t = 1 / v.length();
  return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline float dot(const vec3 &a, const vec3 &b) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline vec3 sqrt(const vec3 &e) {
  return vec3(sqrt(e[0]), sqrt(e[1]), sqrt(e[2]));
}


vec3 draw_from_unit_ball(void) {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0, 1.0, 1.0);
  } while (p.length() >= 1.0);
  return p;
}
