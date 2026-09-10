#include <stdio.h>

int main()
{
    /*
     * Basically auto but on steroids.
     * It will try to find a free register so that it is much faster.
     */

    register int a;
    for (a = 0; a < 5; a++)
    {
        printf("%d ", a);
    }

    /*
     * But the compiler may not always adhere or honor this request of
     * our registers based on our available CPU registers.
     */

    return 0;
}
