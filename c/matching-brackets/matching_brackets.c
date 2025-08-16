#include "matching_brackets.h"
#include <stddef.h>
#include <string.h>

bool is_paired(const char* input) {
  static const char* open = "([{";
  static const char* close = ")]}";
  static const char map[] = {[')'] = '(', [']'] = '[', ['}'] = '{'};

  if (input == NULL || *input == '\0') return true;

  char stack[1024];
  int sp = -1;
  for (; *input != '\0'; ++input) {
    const unsigned char curr = *input;
    if (strchr(open, curr)) {
      stack[++sp] = curr;
    } else if (strchr(close, curr)) {
      if (sp >= 0 && sp < 1024 && stack[sp] == map[curr]) {
        sp--;
      } else {
        return false;
      }
    } else {
      continue;
    }
  }

  return sp == -1;
}
