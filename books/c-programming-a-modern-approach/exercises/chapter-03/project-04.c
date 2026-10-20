#include <stdio.h>

int main(void)
{
    int leading, mid, ending;

    printf("Enter phone number [(xxx) xxx-xxxx]: ");
    scanf("(%d) %d-%d", &leading, &mid, &ending);

    printf("You entered %03d.%03d.%04d\n", leading, mid, ending);

    return 0;
}

