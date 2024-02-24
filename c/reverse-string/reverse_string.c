#include "reverse_string.h"
#include <stdlib.h>
#include <string.h>

char* reverse(const char* value) {
    if (!value) return (void*) 0;

    const size_t len = strlen(value);
    char* result = malloc(sizeof(char[len + 1]));

    for (size_t i = 0; i < len; ++i) {
        result[len - i - 1] = value[i];
    }
    result[len] = '\0';

    return result;
}
