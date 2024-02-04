#include "binary_search.h"

const int* binary_search(int value, const int* arr, size_t length) {
    const size_t m = length / 2;
    if (!length || !arr) return (void*) 0;
    if (arr[m] == value) return &arr[m];
    if (length == 1) return (void*)0;
    if (arr[m] < value) return binary_search(value, &arr[m], length - m);
    return binary_search(value, arr, length - m);
}
