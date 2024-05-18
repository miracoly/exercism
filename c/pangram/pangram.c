#include <stddef.h>
#include <ctype.h>
#include "pangram.h"

bool is_pangram(const char* sentence) {
    if (!sentence) return false;
    bool alphabet[26] = {false};

    while (*sentence) {
        if (isalpha(*sentence)) {
            const size_t i = islower(*sentence)
                             ? *sentence - 'a'
                             : *sentence - 'A';
            alphabet[i] = true;
        }
        sentence++;
    }

    bool result = true;
    for (size_t i = 0; i < 26; ++i) {
        if (!alphabet[i])
            result = false;
    }

    return result;
}
