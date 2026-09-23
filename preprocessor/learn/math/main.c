#include <stdio.h>
#include "math.h"

int main()
{
    printf("%d\n", add(1.5, 5));
    printf("%f", ADD(1.5, 5));    // this is better because it has generic arithmetic
                                // meaning we can add floats if we want without losing precision
}
