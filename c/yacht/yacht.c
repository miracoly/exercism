#include "yacht.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static inline bool all_same_faces(dice_t dice) {
  for (size_t i = 1; i < 5; i++) {
    if (dice.faces[0] != dice.faces[i]) return false;
  }
  return true;
}

static inline int count_all(dice_t dice) {
  int res = 0;
  for (size_t i = 0; i < 5; i++) {
    res += dice.faces[i];
  }
  return res;
}

static inline int count_face(dice_t dice, uint8_t face) {
  int res = 0;
  for (size_t i = 0; i < 5; i++) {
    if (dice.faces[i] == face) {
      res += face;
    }
  }
  return res;
}

static inline int full_house(dice_t dice) {
  int roll[5] = {0};
  for (size_t i = 0; i < 5; i++) {
    roll[dice.faces[i] - 1]++;
  }
  bool found_twos = false;
  bool found_threes = false;
  for (size_t i = 0; i < 5; i++) {
    if (roll[i] == 3) {
      found_threes = true;
    }
    if (roll[i] == 2) {
      found_twos = true;
    }
  }
  return found_twos && found_threes ? count_all(dice) : 0;
}

static inline int four_of_a_kind(dice_t dice) {
  size_t others = 0;
  for (size_t i = 1; i < 5; i++) {
    others += dice.faces[i] == dice.faces[0] ? 0 : 1;
  }
  switch (others) {
    case 0:
      return count_all(dice) - dice.faces[0];
    case 1:
      return count_face(dice, dice.faces[0]);
    case 4:
      return count_face(dice, dice.faces[1]);
    default:
      return 0;
  }
}

static inline int straigth(dice_t dice, uint8_t mask) {
  uint8_t findings = 0;
  for (size_t i = 0; i < 5; i++) {
    findings |= 1 << (dice.faces[i] - 1);
  }
  return findings == mask ? 30 : 0;
}

static inline int little_straight(dice_t dice) {
  return straigth(dice, 0x1F);
}

static inline int big_straight(dice_t dice) {
  return straigth(dice, 0x3E);
}

int score(dice_t dice, category_t category) {
  switch (category) {
    case ONES:
    case TWOS:
    case THREES:
    case FOURS:
    case FIVES:
    case SIXES:
      return count_face(dice, category + 1);
    case FULL_HOUSE:
      return full_house(dice);
    case FOUR_OF_A_KIND:
      return four_of_a_kind(dice);
    case LITTLE_STRAIGHT:
      return little_straight(dice);
    case BIG_STRAIGHT:
      return big_straight(dice);
    case CHOICE:
      return count_all(dice);
    case YACHT:
      return all_same_faces(dice) ? 50 : 0;
    default:
      return 0;
  }
}
