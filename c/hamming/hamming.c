#include "hamming.h"
#include "stdbool.h"

int compute(const char *lhs, const char *rhs) {
    unsigned diff = 0;
    while (true) {
        if ((!*lhs && *rhs) || (*lhs && !*rhs)) { return -1; }
        if (!*lhs || !*rhs) { break; }
        diff += *lhs == *rhs ? 0 : 1;
        lhs++;
        rhs++;
    }
    return diff;
}
