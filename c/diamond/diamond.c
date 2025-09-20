#include "diamond.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char** make_diamond(const char letter) {
  unsigned char l = letter;
  if (l < 'A' || 'Z' < l) return NULL;

  size_t len = (l - 'A') * 2 + 1;
  char** res = calloc(len, sizeof *res);
  if (!res) return NULL;

  size_t i = 0;
  for (; i < len; ++i) {
    res[i] = malloc((sizeof *res[i]) * (len + 1));
    if (!res[i]) goto fail;

    bool bottom = i > (len / 2);
    size_t coll = bottom ? i - (len / 2) : len / 2 - i;
    size_t colr = len - 1 - coll;

    char curr = bottom ? 'A' + (len - 1 - i) : 'A' + i;
    for (size_t j = 0; j < len; ++j) {
      res[i][j] = j == coll || j == colr ? curr : ' ';
    }
    res[i][len] = '\0';
  }
  return res;

fail:
  free_diamond(res);
  return NULL;
}

void free_diamond(char** diamond) {
  if (!diamond) return;

  size_t len = strlen(*diamond);
  for (size_t i = 0; i < len && diamond[i] != NULL; ++i) {
    free(diamond[i]);
  }
  free(diamond);
}
