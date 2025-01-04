#include "sublist.h"
#include <stdbool.h>

static inline bool sublist(const int* long_ls, const int* short_ls,
                           size_t long_count, size_t short_count) {
  for (size_t i = 0; i < long_count; i++) {
    if (long_ls[i] == short_ls[0]) {
      if (long_count - i < short_count) return false;
      else {
        size_t k = 0;
        for (size_t j = i; j < i + short_count; j++) {
          if (long_ls[j] != short_ls[k]) break;
          k++;
        }
        if (k == short_count) return true;
      }
    }
  }
  return false;
}

comparison_result_t check_lists(const int* list_to_compare,
                                const int* base_list,
                                size_t list_to_compare_element_count,
                                size_t base_list_element_count) {
  if (base_list_element_count == 0 && list_to_compare_element_count == 0)
    return EQUAL;
  else if (!list_to_compare && !base_list) return EQUAL;
  else if (!list_to_compare) return SUBLIST;
  else if (!base_list) return SUPERLIST;
  else if (base_list_element_count == list_to_compare_element_count) {
    for (size_t i = 0; i < base_list_element_count; i++) {
      if (list_to_compare[i] != base_list[i]) return UNEQUAL;
    }
    return EQUAL;
  } else if (list_to_compare_element_count < base_list_element_count) {
    bool res = sublist(base_list, list_to_compare, base_list_element_count,
                       list_to_compare_element_count);
    return res ? SUBLIST : UNEQUAL;

  } else {
    bool res = sublist(list_to_compare, base_list,
                       list_to_compare_element_count, base_list_element_count);
    return res ? SUPERLIST : UNEQUAL;
  }
}
