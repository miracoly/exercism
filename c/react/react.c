#include "react.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define REACT_INITIAL_CAPACITY 10

enum Cell_Tag { CELL_INPUT, CELL_COMPUTE1, CELL_COMPUTE2 };

struct Input_Cell {
  int value;
};

struct Compute_Cell_1 {
  int value;
  struct cell* input;
  compute1 fn;
};
struct Compute_Cell_2 {
  int value;
  struct cell* input1;
  struct cell* input2;
  compute2 fn;
};

struct cell {
  enum Cell_Tag tag;
  struct reactor* r;
  union {
    struct Input_Cell ic;
    struct Compute_Cell_1 c1;
    struct Compute_Cell_2 c2;
  } cell;
};

struct reactor {
  size_t count;
  size_t capacity;
  struct cell** cells;
};

static bool add_cell(struct reactor* r, struct cell* c);
static void recompute(struct reactor* r);
static void recompute_cell(struct cell* c);

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

void destroy_reactor(struct reactor* r) {
  if (!r) return;

  for (size_t i = 0; i < r->count; ++i) {
    free(r->cells[i]);
  }
  free(r->cells);
  free(r);
}

struct cell* create_input_cell(struct reactor* r, int initial_value) {
  assert(r != NULL);

  struct cell* c = malloc(sizeof *c);
  if (!c) return NULL;

  c->tag = CELL_INPUT;
  c->r = r;
  c->cell.ic.value = initial_value;
  if (!add_cell(r, c)) {
    free(c);
    return NULL;
  }

  return c;
}

struct cell* create_compute1_cell(struct reactor* r, struct cell* c,
                                  compute1 fn) {
  assert(r != NULL);
  assert(c != NULL);
  assert(fn != NULL);

  struct cell* cc = malloc(sizeof *cc);
  if (!cc) return NULL;

  cc->tag = CELL_COMPUTE1;
  cc->r = r;
  cc->cell.c1.input = c;
  cc->cell.c1.fn = fn;
  cc->cell.c1.value = fn(get_cell_value(c));

  if (!add_cell(r, cc)) {
    free(cc);
    return NULL;
  }

  return cc;
}

struct cell* create_compute2_cell(struct reactor* r, struct cell* c1,
                                  struct cell* c2, compute2 fn) {
  assert(r != NULL);
  assert(c1 != NULL);
  assert(c2 != NULL);
  assert(fn != NULL);

  struct cell* cc = malloc(sizeof *cc);
  if (!cc) return NULL;

  cc->tag = CELL_COMPUTE2;
  cc->r = r;
  cc->cell.c2.input1 = c1;
  cc->cell.c2.input2 = c2;
  cc->cell.c2.fn = fn;
  cc->cell.c2.value = fn(get_cell_value(c1), get_cell_value(c2));

  if (!add_cell(r, cc)) {
    free(cc);
    return NULL;
  }

  return cc;
}

int get_cell_value(struct cell* c) {
  assert(c != NULL);
  switch (c->tag) {
    case CELL_INPUT:
      return c->cell.ic.value;
    case CELL_COMPUTE1:
      return c->cell.c1.value;
    case CELL_COMPUTE2:
      return c->cell.c2.value;
  }
  abort();
}

void set_cell_value(struct cell* c, int new_value) {
  assert(c != NULL);
  assert(c->tag == CELL_INPUT);
  c->cell.ic.value = new_value;
  recompute(c->r);
}

static bool add_cell(struct reactor* r, struct cell* c) {
  assert(r != NULL);
  assert(c != NULL);

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

static void recompute(struct reactor* r) {
  assert(r != NULL);
  for (size_t i = 0; i < r->count; ++i) {
    recompute_cell(r->cells[i]);
  }
}

static void recompute_cell(struct cell* c) {
  assert(c != NULL);
  switch (c->tag) {
    case CELL_INPUT:
      return;
    case CELL_COMPUTE1: {
      const int new_in_val = get_cell_value(c->cell.c1.input);
      c->cell.c1.value = c->cell.c1.fn(new_in_val);
      return;
    }
    case CELL_COMPUTE2: {
      const int new_in_val1 = get_cell_value(c->cell.c2.input1);
      const int new_in_val2 = get_cell_value(c->cell.c2.input2);
      c->cell.c2.value = c->cell.c2.fn(new_in_val1, new_in_val2);
      return;
    }
  }
  abort();
}
