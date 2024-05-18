#include <stdlib.h>
#include <stdint.h>
#include "dnd_character.h"

static uint8_t d6(void){
    return rand() % 6 + 1;
}

int modifier(int score) {
    return (score / 2) - 5;
}

int ability(void) {
    uint8_t min = 6;
    uint8_t result = 0;
    for (size_t i = 0; i < 4; ++i) {
       const uint8_t roll = d6();
       min = min < roll ? min : roll;
       result += roll;
    }
    return result - min;
}

dnd_character_t make_dnd_character(void) {
    const int constitution = ability();
    return (dnd_character_t) {
        .charisma = ability(),
        .constitution = constitution,
        .dexterity = ability(),
        .intelligence = ability(),
        .strength = ability(),
        .wisdom = ability(),
        .hitpoints = 10 + modifier(constitution)
    };
}
