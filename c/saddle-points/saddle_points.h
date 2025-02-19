#ifndef SADDLE_POINTS_H
#define SADDLE_POINTS_H

#include <stdint.h>

typedef struct {
  unsigned row;
  unsigned column;
} saddle_point_t;

typedef struct {
  uint16_t count;
  saddle_point_t points[];
} saddle_points_t;

saddle_points_t*
saddle_points(unsigned rows, unsigned cols, uint8_t matrix[rows][cols]);

void free_saddle_points(saddle_points_t* points);

#endif
