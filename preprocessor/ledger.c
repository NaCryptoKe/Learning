/*
* I implemented using preincrement rather than postincrement
* So the min function does a++ first when trying to evaluate
* so a becomes 5 and b stays 6, which means a is still smaller than b
* after evaluating when printing it does a second increment
* a then becomes 6. 
* so even if we wanted 1 increment we did 2 increments.
*
* THIS IS DETERMINISTIC, SO IT CAN'T BE UB
* It is a double evaluation problem.
*/
#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(void)
{
  int a = 4, b = 6;
  printf("Min is: %d", MIN(++a, b));
}
