#include "rational_numbers.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

static int16_t gcd(int16_t n1, int16_t n2) {
  const int16_t a1 = abs(n1);
  const int16_t a2 = abs(n2);

  if (a1 == a2) return a1;
  else if (a1 < a2) return gcd(a2 - a1, a1);
  else return gcd(a1 - a2, a2);
}

rational_t reduce(rational_t r) {
  if (r.numerator == 0)
    return (rational_t) {
      .numerator = 0,
      .denominator = 1,
    };
  const int16_t _gcd = gcd(r.numerator, r.denominator);
  const int16_t num = r.numerator / _gcd;
  const int16_t den = r.denominator / _gcd;
  const bool neg = r.denominator < 0;

  return (rational_t) {
    .numerator = neg ? -num : num,
    .denominator = neg ? -den : den,
  };
}

rational_t absolute(rational_t r) {
  const rational_t result = (rational_t) {
    .numerator = abs(r.numerator),
    .denominator = abs(r.denominator),
  };
  return reduce(result);
}

// r₁ + r₂ = a₁/b₁ + a₂/b₂ = (a₁ * b₂ + a₂ * b₁) / (b₁ * b₂)
rational_t add(rational_t r1, rational_t r2) {
  const rational_t result = {
    .numerator = (r1.numerator * r2.denominator) +
                 (r2.numerator * r1.denominator),
    .denominator = r1.denominator * r2.denominator
  };
  return reduce(result);
}

// r₁ - r₂ = a₁/b₁ - a₂/b₂ = (a₁ * b₂ - a₂ * b₁) / (b₁ * b₂)
rational_t subtract(rational_t r1, rational_t r2) {
  const rational_t result = {
    .numerator = (r1.numerator * r2.denominator) -
                 (r2.numerator * r1.denominator),
    .denominator = r1.denominator * r2.denominator
  };
  return reduce(result);
}

// r₂ = a₂/b₂ is r₁ * r₂ = (a₁ * a₂) / (b₁ * b₂)
rational_t multiply(rational_t r1, rational_t r2) {
  const rational_t result = {
    .numerator = (r1.numerator * r2.numerator),
    .denominator = r1.denominator * r2.denominator
  };
  return reduce(result);
}

// r₁ / r₂ = (a₁ * b₂) / (a₂ * b₁)
rational_t divide(rational_t r1, rational_t r2) {
  const rational_t result = {
    .numerator = (r1.numerator * r2.denominator),
    .denominator = r1.denominator * r2.numerator
  };
  return reduce(result);
}

static int16_t ipow(int16_t base, uint16_t exp) {
  if (exp == 0) return 1;

  int16_t result = 1;
  for(uint16_t i = 0; i < exp; i++) {
    result *= base;
  }
  return result;
}

rational_t exp_rational(rational_t r, int16_t n) {
  if (n == 0) return (rational_t) {.numerator = 1, .denominator = 1};

  if (r.numerator == 0 && n > 0)
    return (rational_t) {.numerator = 0, .denominator = 1};

  bool negative_exp = (n < 0);
  uint16_t exp_abs = (uint16_t) (negative_exp ? -n : n);

  bool base_is_negative = (r.numerator < 0);
  bool result_is_negative = false;
  if (base_is_negative && (exp_abs % 2 == 1)) {
    result_is_negative = true;
  }

  int16_t a_num = ipow((int16_t) abs(r.numerator), exp_abs);
  int16_t a_den = ipow(r.denominator, exp_abs);

  rational_t result;
  if (!negative_exp) {
    result.numerator = result_is_negative ? -a_num : a_num;
    result.denominator = a_den;
  } else {
    result.numerator = result_is_negative ? -a_den : a_den;
    result.denominator = a_num;
  }

  return result;
}

float exp_real(uint16_t x, rational_t r) {
  const float exp = (float) r.numerator / (float) r.denominator;
  return powf(x, exp);
}
