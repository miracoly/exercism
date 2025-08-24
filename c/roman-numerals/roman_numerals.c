#include "roman_numerals.h"
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 15

static const int base[] = {1,  4,   5,   9,   10,  40,  50,
                           90, 100, 400, 500, 900, 1000};
static const char* symbol[] = {"I",  "IV", "V",  "IX", "X",  "XL", "L",
                               "XC", "C",  "CD", "D",  "CM", "M"};
static const int symbolLen[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};

char* to_roman_numeral(unsigned int number) {
  if (number >= 4000) return NULL;

  char* out = malloc(MAX_LEN + 1);
  if (!out) return NULL;

  int i = sizeof(base) / sizeof(base[0]) - 1;
  char* cur = out;
  while (number > 0) {
    int div = number / base[i];
    while (div) {
      memcpy(cur, symbol[i], symbolLen[i]);
      div--;
      cur += symbolLen[i];
    }
    number = number % base[i];
    i--;
  }
  *cur = '\0';
  char* tmp = realloc(out, cur - out + 1);
  return tmp ? tmp : out;
}
