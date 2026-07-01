#include "react.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define REACT_INITIAL_CAPACITY 10

#define CAT_(a, b) a##b
#define CAT(a, b) CAT_(a, b)
#define VEC(T) CAT(vector_, T)
#define VEC_FN(T, m) CAT(VEC(T), CAT(_, m))

#define DEFINE_VECTOR(T)                              \
  typedef struct VEC(T) {                             \
    size_t length;                                    \
    size_t capacity;                                  \
    T* data;                                          \
  } VEC(T);                                           \
                                                      \
  VEC(T) * VEC_FN(T, new)(size_t capacity) {          \
    VEC(T)* res = malloc(sizeof *res);                \
    if (!res) return NULL;                            \
                                                      \
    res->data = malloc(capacity * sizeof *res->data); \
    if (!res->data) {                                 \
      free(res);                                      \
      return NULL;                                    \
    }                                                 \
                                                      \
    res->capacity = capacity;                         \
    res->length = 0;                                  \
    return res;                                       \
  }                                                   \
                                                      \
  void VEC_FN(T, push_back)(VEC(T) * vec, T elem) {   \
    assert(vec != NULL);                              \
    assert(elem != NULL);                             \
                                                      \
    if (vec->length == vec->capacity) {               \
    //TODO:                                           \
    };                                                \
  }

typedef struct cb {
  callback_id id;
  callback fn;
} cb;

DEFINE_VECTOR(cb)

struct Compute_Cell_1 {
  struct cell* input;
  compute1 fn;
  size_t cb_count;
};
struct Compute_Cell_2 {
  struct cell* input1;
  struct cell* input2;
  compute2 fn;
};

enum Cell_Tag { CELL_INPUT, CELL_COMPUTE1, CELL_COMPUTE2 };

struct cell {
  enum Cell_Tag tag;
  struct reactor* r;
  int value;
  bool changed;
  union {
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
  c->value = initial_value;
  c->changed = false;
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
  cc->changed = false;
  cc->value = fn(get_cell_value(c));
  cc->cell.c1.input = c;
  cc->cell.c1.fn = fn;

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
  cc->changed = false;
  cc->value = fn(get_cell_value(c1), get_cell_value(c2));
  cc->cell.c2.input1 = c1;
  cc->cell.c2.input2 = c2;
  cc->cell.c2.fn = fn;

  if (!add_cell(r, cc)) {
    free(cc);
    return NULL;
  }

  return cc;
}

int get_cell_value(struct cell* c) {
  assert(c != NULL);
  return c->value;
}

void set_cell_value(struct cell* c, int new_value) {
  assert(c != NULL);
  assert(c->tag == CELL_INPUT);
  c->value = new_value;
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
      c->value = c->cell.c1.fn(new_in_val);
      return;
    }
    case CELL_COMPUTE2: {
      const int new_in_val1 = get_cell_value(c->cell.c2.input1);
      const int new_in_val2 = get_cell_value(c->cell.c2.input2);
      c->value = c->cell.c2.fn(new_in_val1, new_in_val2);
      return;
    }
  }
  abort();
}
