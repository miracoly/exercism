#include "etl.h"
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int convert(const legacy_map* input, const size_t input_len, new_map** output) {
  if (!input || input_len == 0) {
    *output = NULL;
    return 0;
  }

  uint8_t tmp['z' + 1] = {0};
  int out_len = 0;
  for (size_t i = 0; i < input_len; ++i) {
    uint8_t points = input[i].value;
    const char* curr = input[i].keys;
    while (*curr) {
      unsigned char low = tolower((unsigned char)*curr);
      tmp[low] = points;
      curr++;
      out_len++;
    }
  }

  *output = malloc(out_len * sizeof **output);
  if (!*output) return 0;

  size_t k = 0;
  for (unsigned char i = 'a'; i <= 'z'; ++i) {
    if (tmp[i] > 0) {
      (*output)[k++] = (new_map){
          .key = i,
          .value = tmp[i],
      };
    }
  }
  return out_len;
}
