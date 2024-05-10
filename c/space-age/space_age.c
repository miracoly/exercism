#include "space_age.h"

#define SECONDS_IN_YEAR 31557600

float const planet_years[NEPTUNE + 1] = {
        [MERCURY] = 0.2408467F,
        [VENUS] = 0.61519726F,
        [EARTH] = 1.0F,
        [MARS] = 1.8808158F,
        [JUPITER] = 11.862615F,
        [SATURN] = 29.447498F,
        [URANUS] = 84.016846F,
        [NEPTUNE] = 164.79132F,
};

static float to_years(int64_t seconds) {
    return (float) seconds / SECONDS_IN_YEAR;
}

float age(planet_t planet, int64_t seconds) {
    if (((int) planet) < MERCURY || ((int) planet) > NEPTUNE) return -1;
    return to_years(seconds) / planet_years[planet];
}
