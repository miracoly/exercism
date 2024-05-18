#include <stdio.h>
#include <string.h>
#include "raindrops.h"

void convert(char result[], int drops) {
    if (!result) return;
    if (drops % 3 == 0)
        strcat(result, "Pling");
    if (drops % 5 == 0)
        strcat(result, "Plang");
    if (drops % 7 == 0)
        strcat(result, "Plong");
    if (!*result)
        sprintf(result, "%d", drops);
}
