#include "spiral_matrix.h"
#include <stdlib.h>

static spiral_matrix_t* fill_matrix(spiral_matrix_t* spiral) {
  if (!spiral->matrix) return spiral;

  struct {
    int top;
    int bottom;
    int right;
    int left;
  } boundaries = {
    0,
    .right = spiral->size - 1,
    .bottom = spiral->size - 1,
    .left = 0,
  };
  int x = 0;
  int y = 0;
  int n = 1;

  const int n_total = spiral->size * spiral->size;
  while(n <= n_total) {
    while(x <= boundaries.right) {
      spiral->matrix[y][x++] = n++;
    }
    x--;
    y++;
    boundaries.top++;
    while(y <= boundaries.bottom) {
      spiral->matrix[y++][x] = n++;
    }
    y--;
    x--;
    boundaries.right--;
    while(x >= boundaries.left) {
      spiral->matrix[y][x--] = n++;
    }
    x++;
    y--;
    boundaries.bottom--;
    while(y >= boundaries.top) {
      spiral->matrix[y--][x] = n++;
    }
    y++;
    x++;
    boundaries.left++;
  }
  return spiral;
}

spiral_matrix_t* spiral_matrix_create(size_t size) {
  spiral_matrix_t* result = calloc(1, sizeof(*result));
  if (!result) return NULL;

  result->size = size;
  if (size == 0) return result;

  result->matrix = calloc(1, size * sizeof(int*) + size * size * sizeof(int));
  if (!result->matrix) {
    free(result);
    return NULL;
  }

  int* data = (int*) (size + result->matrix);

  for(size_t i = 0; i < size; ++i) {
    result->matrix[i] = &data[i * size];
  }

  fill_matrix(result);

  return result;
}

void spiral_matrix_destroy(spiral_matrix_t* spiral) {
  free(spiral->matrix);
  free(spiral);
}
