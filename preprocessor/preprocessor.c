/*
 * preprocessor.c
 *
 * A simple tour of the C PREPROCESSOR.
 * The preprocessor is a text substitution engine that runs BEFORE compilation.
 * Try:  gcc -E preprocessor.c -o preprocessor.i   to see its raw output
 *       (comments gone, #includes pasted in, macros expanded, conditionals resolved)
 */
#include <stdio.h>
#include "foo.h"        /* file inclusion: the whole file gets pasted right here */

/* ============================================================
 * 1. Object-like macros  (#define NAME value)
 *    The preprocessor literally copy-pastes the text.
 *    No type checking, no memory, just text.
 * ============================================================ */

#define Y 5
#define LIMIT (1024 * 4)    /* parenthesized: computed at compile time, not by the preprocessor */

/* ============================================================
 * 2. Function-like macros  (#define NAME(params) body)
 *    Wrap every parameter in parens — otherwise operator
 *    precedence bites you:  SQUARE(1 + 2) would be 1 + 2*1 + 2 = 5
 * ============================================================ */

#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* ============================================================
 * 3. Stringification  (#) — turns an argument into a string literal
 * ============================================================ */

#define PRINT(x) printf(#x " = %d\n", (x))

/* ============================================================
 * 4. Token pasting  (##) — glues two tokens into one identifier
 * ============================================================ */

#define MAKE_VAR(name) var_##name

/* ============================================================
 * 5. Variadic macros  (__VA_ARGS__)
 *    ## eats the trailing comma when no extra args are passed
 * ============================================================ */

#define LOG(fmt, ...) fprintf(stderr, "[%s: %d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

/* ============================================================
 * 6. Built-in macros — the preprocessor fills these in for you
 * ============================================================ */

#define WHERE() printf("in %s at %s:%d\n", __func__, __FILE__, __LINE__)

/* ============================================================
 * 7. Conditional compilation — the preprocessor keeps or
 *    deletes whole blocks of code before the compiler sees it
 * ============================================================ */

#define USE_COLOR 1
/* #define DISABLED_FEATURE */     /* commented out: block below is skipped */

int main(void)
{
    int var_alpha = 10, var_beta = 20;

    /* object-like macros expand to plain text */
    printf("Y = %d, LIMIT = %d\n", Y, LIMIT);

    /* function-like macros expand inline: no call overhead */
    printf("SQUARE(4) = %d, MAX(3, 7) = %d\n", SQUARE(4), MAX(3, 7));

    /* stringification prints the expression *and* its value */
    PRINT(2 + 3);
    PRINT(Y * 2);

    /* token pasting created var_alpha and var_beta above */
    printf("var_alpha = %d, var_beta = %d\n", MAKE_VAR(alpha), MAKE_VAR(beta));

    /* variadic macro: 0 or more args after fmt */
    LOG("plain log line");
    LOG("value is %d", var_alpha);

    /* built-in macros */
    WHERE();
    printf("compiled on line %d of %s\n", __LINE__, __FILE__);
    /* #include "foo.h" pasted `int x;` up top — a file-scope
     * tentative definition we can just use */
    printf("x from foo.h = %d\n", x);

#if USE_COLOR
    printf("color support is ON\n");
#elif !defined(DISABLED_FEATURE)
    printf("color support is OFF\n");
#endif

#ifdef DISABLED_FEATURE
    printf("you should never see this — the block was deleted by the preprocessor\n");
#endif

    return 0;
}
