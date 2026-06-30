#include "react.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
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

static bool add_cell(struct reactor* r, struct cell* c) {
  if (r->count == r->capacity) {
    const size_t new_cap = r->capacity * 2;
    struct cell** new_cs = realloc(r->cells, new_cap * sizeof *r->cells);
    if (!new_cs) return false;

    r->capacity = new_cap;
    r->cells = new_cs;
  }

  r->cells[r->count++] = c;
  return true;
}

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

struct cell* create_input_cell(struct reactor* r, int initial_value) {
  if (!r) return NULL;

  struct cell* c = malloc(sizeof *c);
  if (!c) return NULL;

  c->value = initial_value;
  if (!add_cell(r, c)) {
    free(c);
    return NULL;
  }
  return c;
}
