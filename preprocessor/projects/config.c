#include "config.h"

int items[MAX_ITEMS];

int main (void)
{
#if VERSION == 1
    printf("VERSION 1\n");
#elif VERSION == 2
    printf("VERSION 2\n");
#else
    printf("VERSION NOT SPECIFIED\n");
#endif
  debug_print("this only prints when DEBUG is 1\n");

  int i = 3;
  printf("SQUARE(i) = %d \n", SQUARE(i));

  return 0;
}
