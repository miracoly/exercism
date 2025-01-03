#include "yacht.h"

#include <stdbool.h>
#include <stdlib.h>

static inline bool all_same_faces(dice_t dice) {
  for (size_t i = 1; i < 5; i++) {
    if (dice.faces[0] != dice.faces[i]) return false;
  }
  return true;
}

int score(dice_t dice, category_t category) {
  int res = 0;

  switch (category) {
    case ONES:
      for (size_t i = 0; i < 5; i++) {
        if (dice.faces[i] == 1) {
          res++;
        }
      }
      return res;
    case YACHT:
      return all_same_faces(dice) ? 50 : 0;
    default:
      return 0;
  }
}
