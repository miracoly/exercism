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
    const size_t len = strlen(input);
    int res = 0;

    for (size_t i = len; i > 0; --i) {
        const int dez = to_dez(input[i - 1]);
        if (dez == INVALID) return INVALID;
        res += dez == 1 ? pow(2 * dez, len - i) : 0;
    }

    return res;
}
