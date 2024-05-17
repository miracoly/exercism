#include "queen_attack.h"
#include <stdbool.h>
#include <stdlib.h>

static bool isOnBoard(position_t pos) {
    return pos.row < 8 && pos.column < 8;
}

static bool areEqual(position_t pos1, position_t pos2) {
    return pos1.row == pos2.row && pos1.column == pos2.column;
}

static bool areValid(position_t pos1, position_t pos2) {
    return isOnBoard(pos1) && isOnBoard(pos2) && !areEqual(pos1, pos2);
}

attack_status_t can_attack(position_t queen_1, position_t queen_2) {
    if (!areValid(queen_1, queen_2)) return INVALID_POSITION;
    if (queen_1.row == queen_2.row || queen_1.column == queen_2.column) return CAN_ATTACK;
    if (abs(queen_1.row - queen_2.row) == abs(queen_1.column - queen_2.column)) return CAN_ATTACK;
    return CAN_NOT_ATTACK;
}
