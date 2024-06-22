#include "triangle.h"

static inline bool is_triangle(triangle_t t) {
  return t.a > 0 && t.b > 0 && t.c > 0
         && t.a + t.b >= t.c
         && t.b + t.c >= t.a
         && t.a + t.c >= t.b;
}

bool is_equilateral(triangle_t triangle) {
  return is_triangle(triangle)
         && triangle.a == triangle.b
         && triangle.b == triangle.c;
}

bool is_isosceles(triangle_t triangle) {
  return is_triangle(triangle)
         && (triangle.a == triangle.b
             || triangle.b == triangle.c
             || triangle.a == triangle.c);
}

bool is_scalene(triangle_t triangle) {
  return is_triangle(triangle)
         && !is_equilateral(triangle)
         && !is_isosceles(triangle);
}
