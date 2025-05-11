/*
 * debug.h - Plain C debug utilities (inspired by https://codeforces.com/blog/entry/68809)
 */
#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Helper macros for type-generic printing in C using _Generic */
#define __print(x) _Generic((x),           \
    int: __print_int,                      \
    long: __print_long,                    \
    long long: __print_llong,              \
    unsigned: __print_uint,                \
    unsigned long: __print_ulong,          \
    unsigned long long: __print_ullong,    \
    float: __print_float,                  \
    double: __print_double,                \
    long double: __print_ldouble,          \
    char: __print_char,                    \
    char*: __print_cstr,                   \
    const char*: __print_cstr,             \
    bool: __print_bool,                    \
    default: __print_unknown               \
)(x)

static inline void __print_int(int x) { fprintf(stderr, "%d", x); }
static inline void __print_long(long x) { fprintf(stderr, "%ld", x); }
static inline void __print_llong(long long x) { fprintf(stderr, "%lld", x); }
static inline void __print_uint(unsigned x) { fprintf(stderr, "%u", x); }
static inline void __print_ulong(unsigned long x) { fprintf(stderr, "%lu", x); }
static inline void __print_ullong(unsigned long long x) { fprintf(stderr, "%llu", x); }
static inline void __print_float(float x) { fprintf(stderr, "%f", x); }
static inline void __print_double(double x) { fprintf(stderr, "%lf", x); }
static inline void __print_ldouble(long double x) { fprintf(stderr, "%Lf", x); }
static inline void __print_char(char x) { fprintf(stderr, "'%c'", x); }
static inline void __print_cstr(const char *x) { fprintf(stderr, "\"%s\"", x); }
static inline void __print_bool(bool x) { fprintf(stderr, "%s", x ? "true" : "false"); }
static inline void __print_unknown(void *x) { fprintf(stderr, "<unknown>"); }

/* Print a single variable name and value */
#define __debug_print(x) do {                     \
    fprintf(stderr, "[%s] = ", #x);               \
    __print(x);                                   \
    fprintf(stderr, "\n");                        \
} while (0)

/* Macro overloading up to 10 arguments */
#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME
#define debug(...) GET_MACRO(__VA_ARGS__, \
    debug10, debug9, debug8, debug7, debug6, debug5, \
    debug4, debug3, debug2, debug1)(__VA_ARGS__)

#define debug1(x1) __debug_print(x1)
#define debug2(x1,x2) __debug_print(x1); __debug_print(x2)
#define debug3(x1,x2,x3) __debug_print(x1); __debug_print(x2); __debug_print(x3)
#define debug4(x1,x2,x3,x4) __debug_print(x1); __debug_print(x2); __debug_print(x3); __debug_print(x4)
#define debug5(x1,x2,x3,x4,x5) __debug_print(x1); __debug_print(x2); __debug_print(x3); __debug_print(x4); __debug_print(x5)
#define debug6(x1,x2,x3,x4,x5,x6) __debug_print(x1); __debug_print(x2); __debug_print(x3); __debug_print(x4); __debug_print(x5); __debug_print(x6)
#define debug7(x1,x2,x3,x4,x5,x6,x7) __debug_print(x1); __debug_print(x2); __debug_print(x3); __debug_print(x4); __debug_print(x5); __debug_print(x6); __debug_print(x7)
#define debug8(x1,x2,x3,x4,x5,x6,x7,x8) __debug_print(x1); __debug_print(x2); __debug_print(x3); __debug_print(x4); __debug_print(x5); __debug_print(x6); __debug_print(x7); __debug_print(x8)
#define debug9(x1,x2,x3,x4,x5,x6,x7,x8,x9) __debug_print(x1); __debug_print(x2); __debug_print(x3); __debug_print(x4); __debug_print(x5); __debug_print(x6); __debug_print(x7); __debug_print(x8); __debug_print(x9)
#define debug10(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10) __debug_print(x1); __debug_print(x2); __debug_print(x3); __debug_print(x4); __debug_print(x5); __debug_print(x6); __debug_print(x7); __debug_print(x8); __debug_print(x9); __debug_print(x10)

/* Enable only in debug builds */
#ifdef DEBUG
#undef DEBUG
#define DEBUG(...) debug(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

#endif /* DEBUG_H */
