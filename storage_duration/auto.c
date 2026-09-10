#include <stdio.h>

/*
 * It lives on the stack
 * It stores garbage when declared
 * Its scope is within the block
 * It gets popped once the end of the block reaches
 */

int main()
{
    // auto is optional cause it is the default
    auto int x = 10;

    {
        auto int y = 20;
    }
    printf("%d", x);
    //printf("%d", y);    // this will cause an error cause y is popped and out of scope
    // It will cause variable isn't declared error
    return 0;
}
