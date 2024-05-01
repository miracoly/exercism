#include "clock.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int hour;
    int minute;
} clock_raw;

static int clock_get_minute(const clock_t clock) {
    char m_str[3];
    memcpy(m_str, clock.text + 3, 2);
    m_str[2] = '\0';
    return atoi(m_str);
}

static int clock_get_hour(const clock_t clock) {
    char h_str[3];
    memcpy(h_str, clock.text, 2);
    h_str[2] = '\0';
    return atoi(h_str);
}

static clock_raw clock_get_raw(const clock_t clock) {
    return (clock_raw) {.hour = clock_get_hour(clock), .minute = clock_get_minute(clock)};
}

clock_t clock_create(int hour, int minute) {
    const int m_raw = (minute >= 0) ? minute % 60 : 60 + (minute % 60);
    const int m_overflow = (minute >= 0) ? minute / 60 : (minute / 60) - 1;
    const int h_adjusted = (hour + m_overflow) % 24;
    const int h_raw = (h_adjusted >= 0) ? h_adjusted : 24 + h_adjusted;
    const int h = m_raw >= 60 ? h_raw + (m_raw / 60) : h_raw;
    const int m = m_raw >= 60 ? m_raw % 60 : m_raw;

    clock_t result = {0};
    sprintf(result.text, "%02d:%02d", h, m);

    return result;
}

clock_t clock_add(clock_t clock, int minute_add) {
    const clock_raw raw_old = clock_get_raw(clock);
    return clock_create(raw_old.hour, raw_old.minute + minute_add);
}

clock_t clock_subtract(clock_t clock, int minute_subtract) {
    const clock_raw raw_old = clock_get_raw(clock);
    return clock_create(raw_old.hour, raw_old.minute - minute_subtract);
}

bool clock_is_equal(clock_t a, clock_t b) {
    return strcmp(a.text, b.text) == 0;
}
