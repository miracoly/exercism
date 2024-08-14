#include <stdio.h>
#include "beer_song.h"

#define MAX_LINE_LENGTH (1024)

void recite(uint8_t start_bottles, uint8_t take_down, char** song) {
  for(size_t i = 0; i < take_down; ++i) {
    size_t const j = i * 3;
    uint8_t const rest = start_bottles - i;
    if (rest == 0) {
      snprintf(song[j], MAX_LINE_LENGTH,
               "No more bottles of beer on the wall, no more bottles of beer.");
      snprintf(song[j + 1], MAX_LINE_LENGTH,
               "Go to the store and buy some more, 99 bottles of beer on the wall.");
    }
    else if (rest == 1) {
      snprintf(song[j], MAX_LINE_LENGTH,
               "1 bottle of beer on the wall, 1 bottle of beer.");
      snprintf(song[j + 1], MAX_LINE_LENGTH,
               "Take it down and pass it around, no more bottles of beer on the wall.");
    } else {
      snprintf(song[j], MAX_LINE_LENGTH,
               "%u bottles of beer on the wall, %u bottles of beer.",
               rest, rest);
      snprintf(song[j + 1], MAX_LINE_LENGTH,
               "Take one down and pass it around, %u bottle%s of beer on the wall.",
               rest - 1, rest == 2 ? "" : "s");
    };
  }
}
