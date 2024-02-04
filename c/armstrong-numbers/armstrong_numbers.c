#include <math.h>
#include "armstrong_numbers.h"

static int get_length_of_number(int n) {
    int length = 1;
    int div = n;
    while (div > 9) {
        div = div / 10;
        length++;
    }
    return length;
}

bool is_armstrong_number(int candidate) {
    if (candidate < 10) { return true; }
    else {
        const int exponent = get_length_of_number(candidate);
        double power_sum = 0;
        int num = candidate;
        for (int i = 1; i <= exponent; ++i) {
            const int base = num % 10;
            power_sum += pow(base, exponent);
            num = num / 10;
        }
        return candidate == power_sum;
    }
}
