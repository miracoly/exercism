#include "prime_factors.h"

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS]) {
  size_t j = 2;
  size_t i = 0;
  uint64_t k = n;
  while(j <= k) {
    if (k % j) {
      j++;
    } else {
      factors[i++] = j;
      k /= j;
    }
  }
  return i;
}
