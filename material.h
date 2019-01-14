#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hitable.h"

struct hit_record;
vec3 unit_vector(const vec3 &v);
vec3 draw_from_unit_ball(void);

vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2*dot(v, n)*n;
}

bool refract(const vec3& v, const vec3& norm, float ni_over_nt, vec3& refracted) {
  vec3 uv = unit_vector(v);
  float sin_incident = dot(uv, norm);
  float discrim = 1.0 - ni_over_nt*ni_over_nt*(1 - sin_incident*sin_incident);

  if (discrim > 0) { // i.e. if 0 <= \theta' < 90, so reflection not happened.
    refracted = ni_over_nt * (uv - sin_incident * norm) - sqrt(discrim) * norm;
    return true;
  } else {
    return false;
  }
}

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


float schlick(float cosine, float ref_idx)
{
  float r0 = (1 - ref_idx) / (1 + ref_idx);

  r0 = r0 * r0;
  return r0 + (1-r0)*pow((1 - cosine), 5);
}

class dielectric : public material {
public:
  dielectric(float ri) : ref_idx(ri) {}

  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3&
                       attenuation, ray& scattered) const {
    attenuation = vec3(1, 1, 1);
    vec3 refracted;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    vec3 outward_norm;
    float ni_over_nt;
    float reflect_prob;
    float cosine = -dot(unit_vector(r_in.direction()), rec.normal);

    if (dot(r_in.direction(), rec.normal) > 0) {  // from inside going out.
      outward_norm = -rec.normal;
      ni_over_nt = ref_idx;
    } else {
      outward_norm = rec.normal;
      ni_over_nt = 1.0 / ref_idx;
      cosine = -cosine;
    }

    // Choose whether to reflect or refract.
    if (refract(r_in.direction(), outward_norm, ni_over_nt, refracted)) {
      reflect_prob = schlick(cosine, ref_idx);
      if (drand48() < reflect_prob) {
        scattered = ray(rec.p, refracted);
        return true;
      }
    }

    scattered = ray(rec.p, reflected);
    return true;

  }

  float ref_idx;
};

#endif
