#include "resistor_color_trio.h"

static ohm_unit_t to_unit(resistor_band_t value) {
    return (ohm_unit_t) value / 3;
}

static uint16_t factor(resistor_band_t value) {
    switch (value % 3) {
        case 0: return 1;
        case 1: return 10;
        default: return 100;
    }
}

resistor_value_t color_code(const resistor_band_t code[3]) {
    ohm_unit_t unit = to_unit(code[2]);
    uint16_t value = (10 * code[0] + code[1]) * factor(code[2]);

    if (value && !(value % 1000)) {
        value /= 1000;
        unit += 1;
    }
    return (resistor_value_t) {
            .value = value,
            .unit = unit,
    };

}
