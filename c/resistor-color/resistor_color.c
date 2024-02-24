#include "resistor_color.h"

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

uint16_t color_code(const resistor_band_t color) {
    return code[color];
}

const resistor_band_t* colors() {
    static const resistor_band_t all_colors[WHITE + 1] = {
            [0] = BLACK,
            [1] = BROWN,
            [2] = RED,
            [3] = ORANGE,
            [4] = YELLOW,
            [5] = GREEN,
            [6] = BLUE,
            [7] = VIOLET,
            [8] = GREY,
            [9] = WHITE,
    };

    return all_colors;
}
