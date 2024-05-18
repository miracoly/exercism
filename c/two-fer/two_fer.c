#include <stdio.h>
#include "two_fer.h"

void two_fer(char* buffer, const char* name) {
    if (!buffer) return;
    sprintf(buffer, "One for %s, one for me.", name != NULL ? name : "you");
}
