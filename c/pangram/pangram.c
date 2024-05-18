#include <stddef.h>
#include <ctype.h>
#include <stdint.h>
#include "pangram.h"

bool is_pangram(const char* sentence) {
    if (!sentence) return false;

    uint32_t result = 0;
    while (*sentence) {
        if (isalpha(*sentence)) {
            const size_t i = islower(*sentence)
                             ? 1 << (*sentence - 'a')
                             : 1 << (*sentence - 'A');
            result |= i;
        }
        sentence++;
    }

    return result == 67108863;
}
