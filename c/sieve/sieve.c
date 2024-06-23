#include <stdlib.h>
#include "sieve.h"

#define MAX_PRIMES 1001

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes) {
  if (!primes || limit < 2) return 0;

  uint32_t not_prime_Mask[MAX_PRIMES] = {0};
  uint32_t count = 0;
  size_t k = 0;

  for(size_t i = 2; i <= limit && count < max_primes; ++i) {
    if (!not_prime_Mask[i]) {
      primes[k++] = i;
      count++;
      uint32_t mult = i + i;
      while(mult <= limit) {
        not_prime_Mask[mult] = 1;
        mult += i;
      }
    }
  }
  
  return count;
}
