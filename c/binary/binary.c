#include <string.h>
#include <tgmath.h>
#include "binary.h"

static int to_dez(char binary) {
    if (binary == '0') return 0;
    else if (binary == '1') return 1;
    else return INVALID;
}

int convert(const char* input) {
    if (!input) return INVALID;
    int res = 0;

    for (size_t i = 0; input[i] != '\0'; ++i) {
        res <<= 1;
        const int dez = to_dez(input[i]);
        if (dez == INVALID) return INVALID;
        res += dez;
    }

    return res;
}
