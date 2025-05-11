#include "phone_number.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static bool isValid(char c) {
  return c >= '0' && c <= '9';
}

static bool isValidPhone(size_t len, const char num[len]) {
  return ((len == 11 && num[0] == '1' && num[1] >= '2' && num[4] >= '2') ||
          (len == 10 && num[0] >= '2' && num[3] >= '2'));
}

char* phone_number_clean(const char* input) {
  char* res = calloc(12, sizeof(char));
  int i = 0;
  int len = 0;
  while (input[i] != '\0') {
    if (isValid(input[i])) {
      res[len++] = input[i];
    }
    i++;
  }

  if (!isValidPhone(len, res)) {
    strncpy(res, "0000000000", 11);
    res[10] = '\0';
  }

  if (len == 11 && res[0] == '1') {
    memmove(res, res + 1, 10);
  }
  res[10] = '\0';

  return res;
}
