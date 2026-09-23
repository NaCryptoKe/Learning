#ifndef MACRO_C
#define MACRO_C

/* ============================================================
 * Object-like Macros
 * ============================================================ */

#define Y 5
#define LIMIT (1024 * 4)        // this gets computed in coompilation phase, not preprocessing one

/* ============================================================
 * Function-like Macros
 * ============================================================ */

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SQUARE(x) ((x) * (x))

/* ============================================================
 * Stringification
 * ============================================================ */

#define PRINT(x) printf(#x " = %d\n", (x))

/* ============================================================
 * Token Pasting
 * ============================================================ */

#define MAKE_VAR(x) value_##x

/* ============================================================
 * Variadic Macros
 * ============================================================ */

#define LOG(...) printf(__VA_ARGS__)
#define LOG_INFO(...) printf("[INFO] " __VA_ARGS__)
#define LOG_WARN(...) printf("[WARN] " __VA_ARGS__)
#define LOG_ERROR(...) printf("[ERROR] " __VA_ARGS__)

/* ============================================================
 * Built-in Macro Helper
 * ============================================================ */

#define DEBUG()                                                     \
    printf("FILE: %s\nLINE: %d\nFUNC: %s\n\n",                      \
           __FILE__,                                                \
           __LINE__,                                                \
           __func__)

/* ============================================================
 * Useful Utility Macro
 * ============================================================ */

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* ============================================================
 * X-Macro List
 * ============================================================ */

#define FRUITS      \
    X(APPLE)        \
    X(BANANA)       \
    X(MANGO)        \
    X(ORANGE)
#endif
