#include <stdio.h>

int counter;

void increment(void) {
    int counter = 0;
    counter++;
    printf("%d\n", counter);
}

int main(void) {
    increment();
    increment();
    increment();
    return 0;
}
