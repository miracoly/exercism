#include "flower_field.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static size_t count_neighbors(const char** garden, int rows, int cols, int r,
                              int c) {
  size_t count = 0;
  for (int i = r - 1; i <= r + 1; ++i) {
    for (int j = c - 1; j <= c + 1; ++j) {
      if (0 <= i && i < rows && 0 <= j && j < cols) {
        if (garden[i][j] == '*') count++;
      }
    }
  }
  return count;
}

char** annotate(const char** garden, const size_t rows) {
  if (!garden || rows == 0) return NULL;

  const size_t cols = strlen(*garden);
  char** res = malloc((rows + 1) * sizeof *res);
  if (!res) return NULL;

  size_t rows_allocated = 0;
  for (size_t r = 0; r < rows; ++r, ++rows_allocated) {
    res[r] = malloc(cols + 1);
    if (!res[r]) goto fail;
    for (size_t c = 0; c < cols; ++c) {
      if (garden[r][c] == ' ') {
        size_t count = count_neighbors(garden, rows, cols, r, c);
        res[r][c] = count > 0 ? '0' + count : ' ';
      } else {
        res[r][c] = garden[r][c];
      }
    }
    res[r][cols] = '\0';
  }
  res[rows] = NULL;

  return res;

fail:
  for (size_t i = 0; i < rows_allocated; ++i) {
    free(res[i]);
  }
  free(res);

  return NULL;
}

void free_annotation(char** annotation) {
  if (!annotation) return;

  char** curr = annotation;
  while (*curr) {
    free(*curr);
    curr++;
  }
  free(annotation);
}
