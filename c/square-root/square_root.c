#include "square_root.h"
#include "stdint.h"

unsigned int square_root(unsigned int n) {
    for (int i = 1; i < INT16_MAX; ++i) {
        if (i * i == n) { return i; }
    }
    return 0;
}
