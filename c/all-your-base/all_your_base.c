#include "all_your_base.h"

#include <stdint.h>
#include <stdlib.h>

static size_t _pow(const size_t base, const size_t exp) {
  size_t result = 1;
  for (size_t i = 0; i < exp; i++) {
    result *= base;
  }
  return result;
}

static int8_t to_dez(const int8_t* digits, int8_t input_base, size_t input_len,
                     size_t* out_dez) {
  *out_dez = 0;
  for (size_t i = 0; i < input_len; i++) {
    if (digits[i] < 0 || digits[i] >= input_base) return -1;
    const size_t exp = input_len - i - 1;
    *out_dez += digits[i] * _pow(input_base, exp);
  }
  return 0;
}

static size_t convert_to_base(size_t dez, int16_t out_base,
                              int8_t* out_digits) {
  size_t len = 0;

  do {
    out_digits[len++] = dez % out_base;
    dez /= out_base;
  } while (dez > 0);

  for (size_t i = 0; i < len / 2; i++) {
    int8_t temp = out_digits[i];
    out_digits[i] = out_digits[len - 1 - i];
    out_digits[len - 1 - i] = temp;
  }

  return len;
}

size_t rebase(int8_t* digits, int16_t input_base, int16_t output_base,
              size_t input_len) {
  if (digits == NULL || input_base < 2 || output_base < 2 || input_len < 1)
    return 0;

  size_t dez = 0;
  const size_t error = to_dez(digits, input_base, input_len, &dez);
  if (error) return 0;

  return convert_to_base(dez, output_base, digits);
}
