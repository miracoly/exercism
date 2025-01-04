#include "scrabble_score.h"
#include <ctype.h>
#include <stdint.h>

static inline uint8_t score_letter(char c) {
  if (!isalnum(c)) return 0;
  const char sanitized = islower(c) ? c - ('a' - 'A') : c;

  switch (sanitized) {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'L':
    case 'N':
    case 'R':
    case 'S':
    case 'T':
      return 1;
    case 'D':
    case 'G':
      return 2;
    case 'B':
    case 'C':
    case 'M':
    case 'P':
      return 3;
    case 'F':
    case 'H':
    case 'V':
    case 'W':
    case 'Y':
      return 4;
    case 'K':
      return 5;
    case 'J':
    case 'X':
      return 8;
    case 'Q':
    case 'Z':
      return 10;
    default:
      return 0;
  }
}

unsigned int score(const char* word) {
  if (!word) return 0;
  unsigned int res = 0;
  while (*word) {
    res += score_letter(*word);
    word++;
  }
  return res;
}
