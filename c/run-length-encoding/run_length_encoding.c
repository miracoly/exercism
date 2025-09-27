#include "run_length_encoding.h"
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

char* encode(const char* text) {
  if (!text) return NULL;

  const size_t init_len = strlen(text);
  char* out = malloc(init_len + 1);
  if (!out) return NULL;

  size_t len = 0;
  size_t count = 1;
  for (size_t i = 0; i < init_len; ++i) {
    char next = i == init_len - 1 ? '\0' : text[i + 1];
    if (text[i] == next) {
      count++;
      continue;
    }

    if (count > 1) {
      len += (size_t)snprintf(out + len, init_len + 1 - len, "%zu", count);
      count = 1;
    }
    out[len++] = text[i];
  }

  char* new_out = realloc(out, len + 1);
  if (new_out) {
    out = new_out;
  }
  out[len] = '\0';
  return out;
}

char* decode(const char* data) {
  if (!data) return NULL;

  char* out = malloc(MAX_LEN);
  if (!out) return NULL;

  size_t len = 0;
  while (*data) {
    if (isdigit((unsigned char)*data)) {
      char* end = NULL;
      size_t count = (size_t)strtoul(data, &end, 10);
      data = end;
      while (count--) {
        out[len++] = *data;
      }
    } else {
      out[len++] = *data;
    }
    data++;
  }
  out[len] = '\0';
  return out;
}
