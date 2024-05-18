#include <string.h>
#include "perfect_numbers.h"

kind classify_number(int num) {
    if (num < 1) return ERROR;

    unsigned aliquote_sum = 0;
    for (size_t i = 1; (int) i <= (num / 2); ++i) {
        if (num % i == 0) {
            aliquote_sum += i;
        }
    }

    if ((int) aliquote_sum ==  num) return PERFECT_NUMBER;
    else if ((int) aliquote_sum <  num) return DEFICIENT_NUMBER;
    else return ABUNDANT_NUMBER;
}
