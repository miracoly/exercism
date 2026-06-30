#include "react.h"
#include <stddef.h>
#include <stdlib.h>

#define REACT_INITIAL_CAPACITY 10

struct cell {
  int value;
};

struct reactor {
  size_t count;
  size_t capacity;
  struct cell** cells;
};

struct reactor* create_reactor(void) {
  struct reactor* r = malloc(sizeof *r);
  if (!r) return NULL;

  r->cells = malloc(REACT_INITIAL_CAPACITY * sizeof *r->cells);
  if (!r->cells) {
    free(r);
    return NULL;
  }

  r->count = 0;
  r->capacity = REACT_INITIAL_CAPACITY;
  return r;
}
