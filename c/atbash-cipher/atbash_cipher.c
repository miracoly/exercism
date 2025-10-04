#include "atbash_cipher.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static const char CIPHER[] = "zyxwvutsrqponmlkjihgfedcba";

char* atbash_encode(const char* input) {
  if (!input) return NULL;

  const size_t len = (size_t)strlen(input);
  if (len < 1) return NULL;

  const size_t size = len + (len / 5) + 1;
  char* out = malloc(size);
  if (!out) return NULL;

  size_t k = 0;
  size_t cn = 0;
  for (size_t i = 0; i < len; ++i) {
    unsigned char curr = (unsigned char)input[i];
    if (!isalnum(curr)) continue;

    char cipher = isalpha(curr) ? CIPHER[tolower(curr) - 'a'] : curr;
    out[k++] = cipher;
    cn++;
    if (cn == 5) {
      out[k++] = ' ';
      cn = 0;
    }
  }

  if (k > 0 && out[k - 1] == ' ') {
    out[k - 1] = '\0';
  } else {
    out[k] = '\0';
  }

  return out;
}

char* atbash_decode(const char* input) {
  if (!input) return NULL;

  const size_t len = (size_t)strlen(input);
  if (len < 1) return NULL;

  char* out = malloc(len + 1);
  if (!out) return NULL;

  size_t k = 0;
  for (size_t i = 0; i < len; ++i) {
    unsigned char curr = (unsigned char)input[i];
    if (curr == ' ') continue;

    char plain = isalpha(curr) ? CIPHER[curr - 'a'] : curr;
    out[k++] = plain;
  }

  out[k] = '\0';

  return out;
}
