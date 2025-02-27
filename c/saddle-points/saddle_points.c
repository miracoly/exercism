#include "saddle_points.h"
#include <stdlib.h>
#include <string.h>

static uint8_t*
rows_max(unsigned rows, unsigned cols, uint8_t matrix[rows][cols]) {
  uint8_t* rows_max = calloc(1, sizeof(uint8_t) * rows);
  for(size_t r = 0; r < rows; ++r) {
    uint8_t max = matrix[r][0];
    for(size_t c = 1; c < cols; ++c) {
      if (matrix[r][c] > max) {
        max = matrix[r][c];
      }
    }
    rows_max[r] = max;
  }

  return rows_max;
}

static uint8_t*
cols_min(unsigned rows, unsigned cols, uint8_t matrix[rows][cols]) {
  uint8_t* cols_min = calloc(1, sizeof(uint8_t) * cols);
  for(size_t c = 0; c < cols; ++c) {
    uint8_t min = matrix[0][c];
    for(size_t r = 1; r < rows; ++r) {
      if (matrix[r][c] < min) {
        min = matrix[r][c];
      }
    }
    cols_min[c] = min;
  }

  return cols_min;
}

saddle_points_t*
saddle_points(unsigned rows, unsigned cols, uint8_t matrix[rows][cols]) {
  if (rows == 0 || cols == 0 || matrix == NULL) {
    return calloc(1, sizeof(saddle_points_t));
  }

  uint8_t* rmax = rows_max(rows, cols, matrix);
  uint8_t* cmin = cols_min(rows, cols, matrix);

  saddle_point_t points[10] = {0};
  size_t count = 0;
  for(size_t r = 0; r < rows; ++r) {
    for(size_t c = 0; c < cols; ++c) {
      if (matrix[r][c] == rmax[r] && matrix[r][c] == cmin[c]) {
        points[count++] = (saddle_point_t) {.row = r + 1, .column = c + 1};
      }
    }
  }
  free(rmax);
  free(cmin);

  saddle_points_t* result =
    calloc(1, sizeof *result + (sizeof(saddle_point_t) * count));
  memcpy(result->points, &points, sizeof(saddle_point_t) * count);
  result->count = count;
  return result;
}

void free_saddle_points(saddle_points_t* points) {
  free(points);
}
