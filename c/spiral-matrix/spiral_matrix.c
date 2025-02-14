#include "spiral_matrix.h"
#include <stdlib.h>

static spiral_matrix_t* fill_matrix(spiral_matrix_t* spiral) {
  if (!spiral->matrix) return spiral;

  if (spiral->size == 1) {
    spiral->matrix[0][0] = 1;
  } else if (spiral->size == 2) {
    spiral->matrix[0][0] = 1;
    spiral->matrix[0][1] = 2;
    spiral->matrix[1][1] = 3;
    spiral->matrix[1][0] = 4;
  } else if (spiral->size == 3) {
    spiral->matrix[0][0] = 1;
    spiral->matrix[0][1] = 2;
    spiral->matrix[0][2] = 3;
    spiral->matrix[1][2] = 4;
    spiral->matrix[2][2] = 5;
    spiral->matrix[2][1] = 6;
    spiral->matrix[2][0] = 7;
    spiral->matrix[1][0] = 8;
    spiral->matrix[1][1] = 9;
  }
  return spiral;
}

spiral_matrix_t* spiral_matrix_create(size_t size) {
  spiral_matrix_t* result = calloc(1, sizeof(*result));
  if (!result) return NULL;

  result->size = size;
  if (size == 0) return result;

  result->matrix = calloc(1, size * sizeof(int) + size * size * sizeof(int));
  if (!result->matrix) {
    free(result);
    return NULL;
  }

  int* data = (int*)(size + result->matrix);

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
