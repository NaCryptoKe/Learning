#include "config.h"

int items[MAX_ITEMS];

int calls = 0;
int side_effect(void)
{
  calls++;
  return 42;
}

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

  char name[] = "Nahom";
  int score = 10;
  LOG("player %s scored %d points\n", name, score);
  LOG("starting up, no extra args\n");

  PRINT_VAR(score);

  LOG("value: %d\n", side_effect());
  printf("calls = %d\n", calls);

  return 0;
}
