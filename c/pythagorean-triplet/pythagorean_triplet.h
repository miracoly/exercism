#ifndef PYTHAGOREAN_TRIPLET_H
#define PYTHAGOREAN_TRIPLET_H

#include <stddef.h>

typedef struct triplet_t {
  int a;
  int b;
  int c;
} triplet_t;

typedef struct triplets_t {
  size_t count;
  triplet_t triplets[] __attribute__((counted_by(count)));
} triplets_t;

triplets_t* triplets_with_sum(int sum);

void free_triplets(triplets_t* triplets);

#endif
