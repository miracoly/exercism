#include <stdlib.h>
#include "dnd_character.h"

int modifier(int score) {
    return (score / 2) - 5;
}

int ability(void) {
    return rand() % 15 + 3;
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
