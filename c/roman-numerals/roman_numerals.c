#include "roman_numerals.h"
#include <stdlib.h>
#include <string.h>

static const int base[] = {1,  4,   5,   9,   10,  40,  50,
                           90, 100, 400, 500, 900, 1000};
static const char* symbol[] = {"I",  "IV", "V",  "IX", "X",  "XL", "L",
                               "XC", "C",  "CD", "D",  "CM", "M"};

char* to_roman_numeral(unsigned int number) {
  char* out = calloc(1, 100);

  int i = sizeof(base) / sizeof(base[0]) - 1;
  while (number > 0) {
    int div = number / base[i];
    while (div) {
      strcat(out, symbol[i]);
      div--;
    }
    number = number % base[i];
    i--;
  }

  return realloc(out, strlen(out));
}
