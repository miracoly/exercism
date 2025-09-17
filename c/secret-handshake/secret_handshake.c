#include "secret_handshake.h"
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"

static const char* const handshakes[4] = {"wink", "double blink", "close your eyes",
                                    "jump"};

const char** commands(size_t number) {
  const bool reverse = (1u << 4) & number;
  const char** res = calloc(4, sizeof(*res));
  if (number == 0) return res;

  size_t k = 0;
  for (size_t i = 0; i < 4; ++i) {
    size_t mask = 1u << i;
    if (number & mask) {
      res[k++] = handshakes[i];
    }
  }

  if (reverse && k > 1) {
    const char* tmp[4] = {0};
    for (size_t i = 0; i < k; ++i) {
      tmp[i] = res[k - 1 - i];
    }
    memcpy(res, tmp, k * sizeof *res);
  }

  return res;
}
