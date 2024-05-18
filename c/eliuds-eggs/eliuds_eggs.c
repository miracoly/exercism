#include "eliuds_eggs.h"

size_t egg_count(int num) {
    size_t count = 0;
    while (num) {
        count += num % 2 == 0 ? 0 : 1;
        num >>= 1;
    }
    return count;
}

