#include <stdio.h>

int add(int, int);

static int a = 5;
static int c = 8;

int main()
{
    int c;
    printf("%d", add(a, c));
}

int add (int c, int b)
{
    b = 5;
    c = c + a + b;
    return c;
}
