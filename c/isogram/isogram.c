#include "isogram.h"
#include "stdio.h"

bool is_isogram(const char phrase[]) {
    if (phrase == NULL) {
        return false;
    }

    for (size_t i = 0; phrase[i] != 0; ++i) {
        for (size_t j = i + 1; phrase[j] != 0; ++j) {
            if (are_letters_equal(phrase[i], phrase[j])) {
                return false;
            }
        }
    }

    return true;
}

bool are_letters_equal(char c1, char c2) {
    return is_letter(c1)
           && is_letter(c2)
           && to_lower(c1) == to_lower(c2);
}

bool is_letter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int to_lower(char letter) {
    return letter >= 'A' && letter <= 'Z'
           ? letter - ('A' - 'a')
           : letter;
}
