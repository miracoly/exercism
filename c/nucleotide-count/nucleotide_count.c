#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "nucleotide_count.h"

#define MAX_LEN_STR 100

typedef enum {
  A = 0,
  C,
  G,
  T,
  MAX_NUCLEOTIDES
} nucleotides;

char const nucleotides_char[MAX_NUCLEOTIDES] = {
  [A] = 'A',
  [C] = 'C',
  [G] = 'G',
  [T] = 'T'
};

static nucleotides from_char(char c) {
  for(size_t i = 0; i < MAX_NUCLEOTIDES; ++i) {
    if (nucleotides_char[i] == c) return (nucleotides) i;
  }
  return MAX_NUCLEOTIDES;
}

char* count(const char* dna_strand) {
  size_t count[MAX_NUCLEOTIDES + 1] = {0};
  for(size_t i = 0; dna_strand[i] != '\0'; ++i) {
    count[from_char(dna_strand[i])]++;
  }

  char* ret = calloc(MAX_LEN_STR, sizeof(char));

  if (!count[MAX_NUCLEOTIDES]) {
    snprintf(ret, MAX_LEN_STR, "A:%zu C:%zu G:%zu T:%zu", count[A],
             count[C], count[G], count[T]);
  }

  return ret;
}

