/*
 * Internal Linkage (static): variables or functions are limited to a single translation unit.
 * External Linkage (extern): functions and variables need to be shared across multiple files for communication
 */
#include <stdio.h>
#include "config.h" // Copies global_timeout = 30 here

/*
 * If we had another .c file call config.h it will cause a linking error
 * because we defined and declared it
 * Instead if we only did extern int global_timeout;
 * it will work flawlessly and  we give it a value in that .c file
 */

int global_timeout = 20;
int add(int x, int y)
{
    return x + y;
}

/*
 * Basically put only declaration in headers
 * And logic/definition in the .c file
 */

/*
 * The exceptions to this rule are:
 * 1. static: every .c file gets its own isolated copy
 * Good for isolated helpers
 * 2. inline: basically saying pick one instance and delete the rest
 * Very short, performance critical functions in headers.
 */

int main(void)
{
    printf("%d\n", global_timeout);
}
