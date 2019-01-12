#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hitable.h"

struct hit_record;
vec3 unit_vector(const vec3 &v);
vec3 draw_from_unit_ball(void);

class material {
 public:
  virtual bool scatter(const ray& r_in, const hit_record& rec,
                       vec3& attenuation, ray& scattered) const = 0;
};


class lambertian : public material {
public:
  lambertian(const vec3& a) : albedo(a) {}
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3&
                        attenuation, ray& scattered) const {
    scattered = ray(rec.p, rec.normal + draw_from_unit_ball());
    attenuation = albedo;
    return true;
  }

  vec3 albedo;
};


vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2*dot(v, n)*n;
}


class metal: public material {
public:
 metal(const vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3&
                       attenuation, ray& scattered) const {
    vec3 reflected_direction = unit_vector(reflect(r_in.direction(), rec.normal));
    scattered = ray(rec.p, reflected_direction + fuzz*draw_from_unit_ball());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

  vec3 albedo;
  float fuzz;
};


#endif
