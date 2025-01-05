#include "kindergarten_garden.h"
#include <stdlib.h>
#include <string.h>

static inline int row_index(const char* student) {
  return (student[0] - 'A') * 2;
}

static plant_t plant(const char letter) {
  switch (letter) {
    case 'C': {
      return CLOVER;
    }
    case 'G': {
      return GRASS;
    }
    case 'R': {
      return RADISHES;
    }
    case 'V': {
      return VIOLETS;
    }
    default: {
      exit(1);
    }
  }
}

plants_t plants(const char* diagram, const char* student) {
  const int i_row = row_index(student);
  const char* fst_row = diagram;
  const char* m_snd_row = strchr(diagram, '\n');
  if (!m_snd_row) exit(1);
  const char* snd_row = m_snd_row + 1;

  return (plants_t){.plants = {
                        [0] = plant(fst_row[i_row]),
                        [1] = plant(fst_row[i_row + 1]),
                        [2] = plant(snd_row[i_row]),
                        [3] = plant(snd_row[i_row + 1]),
                    }};
}
