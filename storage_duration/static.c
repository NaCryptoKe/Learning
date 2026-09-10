#include <stdio.h>

void counter()
{
    auto int x = 5;     // this gets destroyed once we go out of this block
    static int y = 6;   // this won't

    x++;
    y++;

    printf("%d\t%d\n", x, y);
}
int main()
{
    /*
     * Its scope is local
     * By default they are zero
     * They live on RAM
     * They are available till the end of the program
     */

    counter();  // it prints 6, 7
    counter();  // it prints 6, 8. Because the y value is still available
}
