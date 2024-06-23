#include <stddef.h>
#include "allergies.h"

bool is_allergic_to(allergen_t allergen, unsigned test);

allergen_list_t get_allergens(unsigned test) {
  allergen_list_t res = {0};
  for(allergen_t i = 0; i < ALLERGEN_COUNT; ++i) {
    const bool isAllergicTo = is_allergic_to(i, test);
    res.allergens[i] = isAllergicTo;
    res.count += isAllergicTo;
  }
  return res;
}

