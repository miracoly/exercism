#include "variable_length_quantity.h"
#include <stddef.h>
#include <stdint.h>

int encode(const uint32_t* integers, size_t integers_len, uint8_t* output) {
  if (!integers || !output) return -1;

  size_t idx_out = 0;

  for (size_t i = 0; i < integers_len; ++i) {
    uint32_t v = integers[i];

    int groups = 1;
    for (uint32_t tmp = v >> 7; tmp; tmp >>= 7)
      ++groups;

    while (groups) {
      int shift = (--groups) * 7;
      uint8_t byte = (v >> shift) & 0x7F;
      if (groups) byte |= 0x80;
      output[idx_out++] = byte;
    }
  }
  return idx_out;
}

int decode(const uint8_t* bytes, size_t buffer_len, uint32_t* output) {
  if (!bytes || !output || buffer_len < 1 || bytes[buffer_len - 1] & 0x80)
    return -1;

  size_t idx_out = 0;
  uint32_t curr_num = 0;

  for (size_t i = 0; i < buffer_len; ++i) {
    curr_num <<= 7;
    curr_num += bytes[i] & 0x7F;
    if ((bytes[i] & 0x80) == 0) {
      output[idx_out++] = curr_num;
      curr_num = 0;
    }
  }

  return idx_out;
}
