#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

#define DEBUG 1

// --- LOG: resolved independently for every value of DEBUG ---
#if DEBUG == 1
    #define LOG(fmt, ...) printf("[%s:%d] %s: " fmt, __func__, __LINE__, __FILE__, ##__VA_ARGS__)
    // #define LOG(fmt, ...) printf("[%s:%d] %s: " fmt, __func__, __LINE__, __FILE__ __VA_OPT__(,) __VA_ARGS__)
#else
    #define LOG(fmt, ...)
#endif

// --- debug_print: also resolved independently, not nested inside LOG's branch ---
#if DEBUG == 1
    #define debug_print(msg) printf(msg)
#else
    #define debug_print(msg)
#endif

#define VERSION 2

#define SQUARE(x) ((x) * (x))
// still unsafe for i++, i--, ++i, --i — same value gets evaluated twice

#define MAX_ITEMS 10
extern int items[MAX_ITEMS];

#define PRINT_VAR(x) printf("%s = %d\n", #x, x)

#endif // CONFIG_H
