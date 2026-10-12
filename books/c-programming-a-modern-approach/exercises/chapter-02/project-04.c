#include <stdio.h>

#define TAX_PERCENTAGE 0.05

int main(void)
{
  float price, price_with_tax;

  printf("Enter an amount: ");
  scanf("%f", &price);

  price_with_tax = price + (price * TAX_PERCENTAGE);

  printf("With tax added: $%.2f\n", price_with_tax);

  return 0;
}

