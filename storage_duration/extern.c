#include <stdio.h>

int main()
{
    /*
     * It is available through out the file,
     * It is global
     * Default value is zero
     * Stored on the RAM
     * Lives till the end of the program
     */

    {
        extern int a;
    }

    int a = 10;
    printf("%d", a);
}
