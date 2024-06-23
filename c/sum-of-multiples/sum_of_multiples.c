#include "sum_of_multiples.h"

unsigned
sum(const unsigned* factors, size_t number_of_factors, unsigned limit) {
  if (!factors) return 0;

  unsigned sum = 0;
  for(size_t i = 1; i < limit; ++i) {
    for(size_t j = 0; j < number_of_factors; ++j) {
      if (factors[j] && i % factors[j] == 0) {
        sum += i;
        break;
      }
    }
  }

  return sum;
}
