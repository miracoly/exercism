#include "pascals_triangle.h"
#include <stdint.h>
#include <stdlib.h>

void free_triangle(uint8_t** triangle, size_t rows) {
  for (size_t i = 0; i < rows; i++) {
    free(triangle[i]);
  }
  free(triangle);
}

uint8_t** create_triangle(size_t rows) {
  size_t _rows = rows < 1 ? 1 : rows;
  uint8_t** triangle = malloc(_rows * sizeof(uint8_t*));
  for (size_t i = 0; i < _rows; i++) {
    triangle[i] = calloc(_rows, sizeof(uint8_t));
  }

  if (rows == 0) return triangle;

  for (size_t r = 0; r < _rows; r++) {
    triangle[r][0] = 1;
    triangle[r][r] = 1;
    for (size_t c = 1; c < r; c++) {
      triangle[r][c] = triangle[r - 1][c - 1] + triangle[r - 1][c];
    }
  }
  return triangle;
}
