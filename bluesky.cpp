#include <stdlib.h>
#include <iostream>

#include "camera.h"
#include "hitable.h"
#include "hitablelist.h"
#include "ray.h"
#include "sphere.h"

vec3 color(const ray& r, hitable *world) {
  hit_record rec;
  bool hit = world->hit(r, 0.0, MAXFLOAT, rec);

  if (hit) {
    return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
  }

  vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5*(unit_direction.y() + 1.0);
  return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
  int nx = 200;
  int ny = 100;
  int ns = 100;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  camera cam;
  hitable *list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);
  hitable *world = new hitable_list(list, 2);

  for (int j = 0; j < ny ; j++) {
    for (int i = 0; i < nx ; i++) {
      vec3 col(0.0, 0.0, 0.0);

      for (int s = 0; s < ns; s++) {
        float u = float(i + drand48()) / nx;
        float v = 1.0 - float(j + drand48()) / ny;

        col = col + color(cam.get_ray(u, v), world);
      }
      col = 1/float(ns) * col;

      int *p = col.as_ppm();
      std::cout << p[0] << " " << p[1] << " " << p[2] << std::endl;
    }
  }

}
