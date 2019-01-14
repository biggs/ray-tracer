#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include <math.h>

class vec3;

vec3 draw_random_from_disc(void) {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    } while (dot(p, p) > 1);
    return p;
}

class camera {
public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vup,
            float vfov, float aspect, float aperture, float focal_length) {
		float theta = vfov * M_PI/180;
        /* float scale_size = (lookfrom - lookat).length(); */
		float half_height = tan(theta/2);
		float half_width = aspect * half_height;
        lens_radius = aperture/2;

		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = origin - focal_length * (half_width * u + half_height * v + w);

		hor = 2 * focal_length * half_width * u;
		vert = 2 * focal_length * half_height * v;
	}

	ray get_ray(float s, float t) {
        vec3 r = draw_random_from_disc();
        vec3 offset = lens_radius * (r.x() * u + r.y() * v);
        return ray(origin + offset,
                    lower_left_corner + s*hor + t*vert - origin - offset);
	}

	vec3 origin;
	vec3 lower_left_corner;
	vec3 hor, vert;
	vec3 u, v, w;
    float lens_radius;
};

#endif
