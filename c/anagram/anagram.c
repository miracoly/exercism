#include "anagram.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static char* strtolower(char* str) {
  if (!str) return NULL;

  char* cur = str;
  while (*cur) {
    *cur = isalpha(*cur) ? tolower((unsigned char)*cur) : *cur;
    cur++;
  }
  return str;
}

static void check_anagram(size_t len, const char* subLower,
                          const int occSub[128], struct candidate* c) {
  if (!occSub || !c) return;

  size_t lenC = strlen(c->word);
  if (len != lenC) {
    c->is_anagram = NOT_ANAGRAM;
    return;
  }

  char* cLower = malloc(lenC + 1);
  if (!cLower) return;

  memcpy(cLower, c->word, lenC + 1);
  cLower = strtolower(cLower);

  if (strncmp(subLower, cLower, len) == 0) {
    c->is_anagram = NOT_ANAGRAM;
    free(cLower);
    return;
  }

  int occuranceC[128] = {0};
  for (size_t i = 0; i < len; ++i) {
    occuranceC[(size_t)cLower[i]]++;
  }

  if (memcmp(occSub, occuranceC, sizeof occuranceC)) {
    c->is_anagram = NOT_ANAGRAM;
  } else {
    c->is_anagram = IS_ANAGRAM;
  }

  free(cLower);
}

void find_anagrams(const char* subject, struct candidates* candidates) {
  if (!subject || !candidates) return;

  const size_t len = strlen(subject);
  char* sub = malloc(len + 1);
  if (!sub) return;
  memcpy(sub, subject, len + 1);

  char* subLower = strtolower(sub);
  int occuranceSub[128] = {0};
  for (size_t i = 0; i < len; ++i) {
    occuranceSub[(size_t)subLower[i]]++;
  }

  for (size_t i = 0; i < candidates->count; ++i) {
    check_anagram(len, subLower, occuranceSub, candidates->candidate + i);
  }

  free(sub);
}
