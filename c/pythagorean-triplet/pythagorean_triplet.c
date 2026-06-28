#include "pythagorean_triplet.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct maybe_triplet_t {
  bool has_value;
  triplet_t value;
} maybe_triplet_t;

#define MAYBE_NONE (maybe_triplet_t){0}
#define MAYBE_SOME(...)                       \
  (maybe_triplet_t) {                         \
    .has_value = true, .value = (__VA_ARGS__) \
  }

#define MAYBE_IS_SOME(...) ((__VA_ARGS__).has_value)

static maybe_triplet_t calculate(int a, int sum) {
  int dividend = (2 * a * sum) - (sum * sum);
  int divisor = (2 * a - 2 * sum);
  if (dividend % divisor) return MAYBE_NONE;

  int b = dividend / divisor;
  int c = sum - a - b;
  if (!(a < b && b < c)) return MAYBE_NONE;

  return MAYBE_SOME((triplet_t){.a = a, .b = b, .c = c});
}

triplets_t* triplets_with_sum(int sum) {
  size_t count = 0;
  int bound = sum / 3;
  for (int a = 1; a < bound; ++a) {
    if (MAYBE_IS_SOME(calculate(a, sum))) {
      count++;
    }
  }

  triplets_t* res = malloc(sizeof(triplets_t) + count * sizeof(triplet_t));
  if (!res) return NULL;

  res->count = count;
  if (count == 0) return res;

  size_t k = 0;
  for (int a = 1; a < bound; ++a) {
    maybe_triplet_t m_triplet = calculate(a, sum);
    if (MAYBE_IS_SOME(m_triplet)) {
      res->triplets[k++] = m_triplet.value;
    }
  }
  return res;
}

/*
b = (2*a*sum -sum^2) / (2*a - 2*sum)
*/

void free_triplets(triplets_t* triplets) {
  free(triplets);
}
