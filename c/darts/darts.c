#include "darts.h"
#include <stdbool.h>
#include <tgmath.h>


static float distance(coordinate_t pos) {
    return hypot(pos.x, pos.y);
}

static bool isOuterCircle(coordinate_t pos) {
    return distance(pos) <= 10.0;
}
static bool isMiddleCircle(coordinate_t pos) {
    return distance(pos) <= 5.0;
}
static bool isInnerCircle(coordinate_t pos) {
    return distance(pos) <= 1.0;
}

uint8_t score(coordinate_t pos) {
    if (isInnerCircle(pos)) return 10;
    if (isMiddleCircle(pos)) return 5;
    if (isOuterCircle(pos)) return 1;
    return 0;
}
