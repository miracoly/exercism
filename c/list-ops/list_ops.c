#include "list_ops.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

list_t* new_list(size_t length, list_element_t elements[]) {
    list_t* ls = malloc(sizeof(list_t) + (length * sizeof(list_element_t)));
    if (!ls) return (void*) 0;

    ls->length = length;
    memcpy(ls->elements, elements, sizeof(list_element_t[length]));
    return ls;
}

list_t* append_list(list_t* list1, list_t* list2) {
    if (!list1 || !list2) return (void*) 0;
    const size_t new_length = list1->length + list2->length;
    list_t* ls = malloc(sizeof(list_t) + (new_length * sizeof(list_element_t)));
    ls->length = new_length;
    memcpy(ls->elements, list1->elements, sizeof(list_element_t[list1->length]));
    memcpy(ls->elements + list1->length, list2->elements, sizeof(list_element_t[list2->length]));
    return ls;
}

list_t* filter_list(list_t* list, bool (* filter)(list_element_t)) {
    size_t new_len = 0;
    list_element_t filtered[list->length];
    for (size_t i = 0; i < list->length; ++i) {
        if (filter(list->elements[i])) {
            filtered[new_len] = list->elements[i];
            new_len++;
        }
    }
    return new_list(new_len, filtered);
}

size_t length_list(list_t* list) {
    return list->length;
}

list_t* map_list(list_t* list, list_element_t (* map)(list_element_t)) {
    list_element_t mapped[list->length];
    for (size_t i = 0; i < list->length; ++i) {
        mapped[i] = map(list->elements[i]);
    }
    return new_list(list->length, mapped);
}

list_element_t foldl_list(list_t* list, list_element_t initial,
                          list_element_t (* foldl)(list_element_t,
                                                   list_element_t)) {
    list_element_t folded = initial;
    for (size_t i = 0; i < list->length; ++i) {
        folded = foldl(list->elements[i], folded);
    }
    return folded;
}

list_element_t foldr_list(list_t* list, list_element_t initial,
                          list_element_t (* foldr)(list_element_t,
                                                   list_element_t)) {
    list_element_t folded = initial;
    for (size_t i = list->length; i > 0; --i) {
        folded = foldr(list->elements[i - 1], folded);
    }
    return folded;
}

list_t* reverse_list(list_t* list) {
    list_element_t reversed[list->length];
    for (size_t i = 0; i < list->length; ++i) {
        reversed[i] = list->elements[list->length - i - 1];
    }
    return new_list(list->length, reversed);
}

void delete_list(list_t* list) {
    free(list);
}
