#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class vec3;

class camera {
public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) {
		float theta = vfov * M_PI/180;
        float scale_size = (lookfrom - lookat).length();
		float half_height = scale_size * tan(theta/2);
		float half_width = aspect*half_height;

		origin = lookfrom;
		vec3 w = unit_vector(lookfrom - lookat);
		vec3 u = unit_vector(cross(vup, w));
		vec3 v = cross(w, u);
		lower_left_corner = lookat - half_width * u - half_height * v;

		hor = 2 * half_width * u;
		vert = 2 * half_height * v;
	}

	ray get_ray(float u, float v) {
		return ray(origin, lower_left_corner + u*hor + v*vert - origin);
	}

	vec3 origin;
	vec3 lower_left_corner;
	vec3 hor;
	vec3 vert;
};

#endif
