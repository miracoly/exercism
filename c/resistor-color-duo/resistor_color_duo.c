#include "resistor_color_duo.h"

static const uint16_t code[WHITE + 1] = {
        [BLACK] = 0,
        [BROWN] = 1,
        [RED] = 2,
        [ORANGE] = 3,
        [YELLOW] = 4,
        [GREEN] = 5,
        [BLUE] = 6,
        [VIOLET] = 7,
        [GREY] = 8,
        [WHITE] = 9,
};

uint16_t color_code(const resistor_band_t bands[static 2]) {
    return code[bands[0]] * 10 + code[bands[1]];
}
