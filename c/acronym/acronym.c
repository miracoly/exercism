#include "acronym.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static char* str_copy(const char* str) {
  if (str == NULL) return NULL;

  const size_t len = strlen(str);
  char* cpy = malloc(len + 1);
  if (cpy == NULL) return NULL;

  memcpy(cpy, str, len + 1);
  return cpy;
}

static inline bool isdelim(char c) {
  return c == ' ' || c == '-';
}

static inline bool validchar(char c) {
  return isalpha(c) || isdelim(c);
}

static void sanitize(char* str) {
  if (str == NULL) return;

  char* wr = str;
  for (; *str != '\0'; ++str) {
    if (!isdelim(*str)) {
      break;
    }
  }

  /* bool lastDelim = false; */
  for (; *str != '\0'; ++str) {
    if (!validchar(*str)) {
      continue;
    }
    *wr++ = *str;
  }
  *wr = '\0';
}

static inline size_t count_delims(const char* str) {
  size_t count = 0;
  for (; *str != '\0'; ++str) {
    if (isdelim(*str)) count++;
  }
  return count;
}

char* abbreviate(const char* phrase) {
  if (phrase == NULL) return NULL;
  if (*phrase == '\0') return NULL;

  // duplicate string
  char* str = str_copy(phrase);
  if (str == NULL) return NULL;

  sanitize(str);
  size_t countdelims = count_delims(str);

  // delims + extra word + nullterm
  char* out = malloc(countdelims + 2);
  if (out == NULL) {
    free(str);
    return NULL;
  }

  char* token = strtok(str, " -");
  size_t i = 0;
  while (token) {
    out[i++] = toupper(*token);
    token = strtok(NULL, " -");
  }
  out[i] = '\0';

  free(str);
  return out;
}
