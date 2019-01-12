#include <stdlib.h>
#include <iostream>

#include "camera.h"
#include "hitable.h"
#include "hitablelist.h"
#include "ray.h"
#include "sphere.h"


vec3 draw_from_unit_ball(void) {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0, 1.0, 1.0);
  } while (p.length() >= 1.0);
  return p;
}


vec3 color(const ray& r, hitable *world) {
  hit_record rec;

  if (world->hit(r, 0.001, MAXFLOAT, rec)) {
    /* If hit hittable, generate new ray and follow.
     * Stop on MAXFLOAT or 'sky'.
     */
    ray reflected = ray(rec.p, rec.normal + draw_from_unit_ball());
    return 0.5 * color(reflected, world);
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

      int *p = sqrt(col).as_ppm();
      std::cout << p[0] << " " << p[1] << " " << p[2] << std::endl;
    }
  }

}
