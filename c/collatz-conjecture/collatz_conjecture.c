#include "collatz_conjecture.h"
#include <stdlib.h>

int steps(int start) {
    if (start < 1) return -1;
    int n = start;
    size_t steps = 0;
    while(n != 1) {
        n = n % 2 ? n * 3 + 1 : n / 2;
        steps++;
    }
    return steps;
}
