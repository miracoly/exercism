#include "bob.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool is_question(const char* greeting) {
  if (!greeting) return false;
  unsigned char last = '\0';
  while (*greeting) {
    unsigned char c = *greeting;
    if (!isspace(c)) last = c;
    greeting++;
  };
  return last == '?';
}

static bool is_yelling(const char* greeting) {
  if (!greeting) return false;
  bool has_alpha = false;
  while (*greeting) {
    unsigned char c = *greeting;
    if (isalpha(c)) has_alpha = true;
    if (isalpha(c) && islower(c)) return false;
    greeting++;
  };
  return has_alpha;
}

static bool is_yelled_question(const char* greeting) {
  return is_question(greeting) && is_yelling(greeting);
}

static bool is_silence(const char* greeting) {
  if (!greeting) return false;
  while (*greeting) {
    unsigned char c = *greeting;
    if (!isspace(c)) return false;
    greeting++;
  }
  return true;
}

const char* hey_bob(char* greeting) {
  if (!greeting) return NULL;
  if (is_yelled_question(greeting)) return "Calm down, I know what I'm doing!";
  if (is_question(greeting)) return "Sure.";
  if (is_yelling(greeting)) return "Whoa, chill out!";
  if (is_silence(greeting)) return "Fine. Be that way!";
  else return "Whatever.";
}
