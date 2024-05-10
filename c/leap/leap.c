#include "leap.h"

bool leap_year(int year) {
    if (year % 100 == 0) {
      if (year % 400 == 0) return true;
        return false;
    }
    if (year % 4 == 0) return true;
    return false;
}
