#include "luhn.h"

#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

static size_t trim_whitespace(size_t len, const char in[len], char out[static len]) {
    size_t newLen = 0;
    for (size_t i = 0; i < len; ++i) {
        if (isspace(in[i])) continue;
        out[newLen] = in[i];
        newLen++;
    }
    return newLen;
}

static uint8_t to_digits(size_t len, const char in[len], unsigned out[len]) {
    for (size_t i = 0; i < len; ++i) {
        if (!isdigit(in[i])) return EXIT_FAILURE;
        out[i] = in[i] - '0';
    }
    return EXIT_SUCCESS;
}

static unsigned double_sum(size_t len, const unsigned nums[len]) {
    unsigned sum = 0;
    bool shouldDouble = false;
    for (size_t i = len; i != 0; --i) {
        if (shouldDouble) {
            unsigned d = nums[i - 1] * 2;
            sum += d > 9 ? d - 9 : d;
        } else {
            sum += nums[i - 1];
        }
        shouldDouble = !shouldDouble;
    }
    return sum;
}

bool luhn(const char *num) {
    const size_t len = strlen(num);
    char trimmed[len];
    const size_t newLen = trim_whitespace(len, num, trimmed);
    if (newLen < 2) return false;
    unsigned numbers[newLen];
    const uint8_t invalid = to_digits(newLen, trimmed, numbers);

    if (invalid) return false;

    const unsigned s = double_sum(newLen, numbers);

    return s % 10 == 0;
}
