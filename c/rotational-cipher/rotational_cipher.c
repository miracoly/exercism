#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "rotational_cipher.h"

static inline char rotate_one(char c, uint8_t shift_key) {
  if (!isalpha(c)) return c;

  const uint16_t shifted = c + shift_key;
  if (shifted > CHAR_MAX + 26) return c;
  else
    return (isupper(c) && isupper(shifted)) || (islower(c) && islower(shifted))
           ? (char) shifted
           : (char) shifted - 26;
}

char* rotate(const char* text, int shift_key) {
  if (!text || shift_key > 26) return NULL;

  const size_t len = strlen(text);
  char* rot = calloc(len + 1, sizeof(*text));
  if (!rot) return NULL;

  for(size_t i = 0; i < len; ++i) {
    rot[i] = rotate_one(text[i], shift_key);
  }

  return rot;
}
