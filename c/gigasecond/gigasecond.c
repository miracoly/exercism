#include "gigasecond.h"

void gigasecond(time_t input, char* output, size_t size) {
  time_t const giga = input + 1000000000;
  struct tm* pTm = gmtime(&giga);
  strftime(output, size, "%F %T", pTm);
}
