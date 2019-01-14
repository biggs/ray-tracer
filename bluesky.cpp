#include <stdlib.h>
#include <iostream>

#include "camera.h"
#include "hitable.h"
#include "hitablelist.h"
#include "ray.h"
#include "sphere.h"

vec3 color(const ray& r, hitable *world, int depth) {
  hit_record rec;

  if (world->hit(r, 0.001, MAXFLOAT, rec)) {
    ray scattered;
    vec3 attenuation;  /* color attenuation */
    if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return attenuation * color(scattered, world, depth + 1);
    } else {
      return vec3(0, 0, 0);  // when reach depth=50, return black.
    }
  } else {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
  }
}

int main() {
  int nx = 200;
  int ny = 100;
  int ns = 100;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  camera cam;
  hitable *list[5];
  list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
  list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
  list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
  list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
  list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
  hitable *world = new hitable_list(list, 5);

  for (int j = 0; j < ny ; j++) {
    for (int i = 0; i < nx ; i++) {
      vec3 col(0.0, 0.0, 0.0);

      for (int s = 0; s < ns; s++) {
        float u = float(i + drand48()) / nx;
        float v = 1.0 - float(j + drand48()) / ny;

        col = col + color(cam.get_ray(u, v), world, 0);
      }
      col = 1/float(ns) * col;

      int *p = sqrt(col).as_ppm();
      std::cout << p[0] << " " << p[1] << " " << p[2] << std::endl;
    }
  }

}
