#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "material.h"

class sphere: public hitable {
	public:
		sphere () {}
		sphere (vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m)  {};
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

		vec3 center;
		float radius;
		material *mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(r.direction(), oc);
	float c = dot(oc, oc) - radius * radius;
	float discrim = b*b - 4 * a * c;

	if (discrim > 0) {
		float temp = (- b - sqrt(discrim)) / (2.0 * a);
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = 1/radius * (rec.p - center);
			rec.mat_ptr = mat_ptr;

			return true;
		}

		temp = (- b + sqrt(discrim)) / (2.0 * a);
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = 1/radius * (rec.p - center);
			rec.mat_ptr = mat_ptr;

			return true;
		}
	}

	return false;
}

#endif
