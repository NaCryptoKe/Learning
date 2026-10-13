#include <stdio.h>

int main (void)
{
  int dollar_amount = 0, twenties = 0, tens = 0, fives = 0, ones = 0;

  printf("Enter a dollar amount: ");
  scanf("%d", &dollar_amount);

  twenties = dollar_amount / 20;
  dollar_amount = dollar_amount % 20;

  tens = dollar_amount / 10;
  dollar_amount = dollar_amount % 10;

  fives = dollar_amount / 5;
  dollar_amount = dollar_amount % 5;

  ones = dollar_amount;

  printf("$20 bills: %d\n", twenties);
  printf("$10 bills: %d\n", tens);
  printf(" $5 bills: %d\n", fives);
  printf(" $1 bills: %d\n", ones);

  return 0;
}
