#include <stdbool.h>
#include <stdlib.h>
#include "nth_prime.h"

static bool* primes(uint64_t s) {
  bool* not_primes = calloc(s + 1, sizeof(bool));
  not_primes[0] = true;
  not_primes[1] = true;

  size_t p = 2;
  size_t k = 0;
  while(k < p) {
    for(size_t i = 2 * p; i < s; i += p) {
      not_primes[i] = true;
    }
    k = p;
    for(size_t i = p + 1; i < s; ++i) {
      if (!not_primes[i]) {
        p = i;
        break;
      }
    }
  }

  bool* primes = not_primes;
  for(size_t i = 0; i < s + 1; ++i) {
    primes[i] = !primes[i];
  }

  return primes;
}

static inline size_t sum_primes(size_t len, const bool primes[len]) {
  size_t count = 0;
  for(size_t i = 2; i < len; ++i) {
    count += primes[i];
  }
  return count;
}

uint32_t nth(uint32_t n) {
  size_t count = 0;
  bool* ps = NULL;
  size_t k = 1;
  while(count < n) {
    if (ps) {
      free(ps);
    }
    k++;
    ps = primes(n * k);
    count = sum_primes(n * k, ps);
  }

  size_t i = 1;
  uint32_t res = 0;
  for(uint32_t j = 2; j < (k * n) + 1; ++j) {
    if (ps && ps[j]) {
      if (n == i) {
        res = j;
        break;
      }
      i++;
    }
  }

  free(ps);
  return res;
}
