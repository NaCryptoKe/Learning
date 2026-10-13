#include <stdio.h>

int main(void)
{
  float loan = 0.0f, interest_rate = 0.0f, monthly_payment = 0.0f;

  printf("Enter amount of loan: ");
  scanf("%f", &loan);

  printf("Enter interest rate: ");
  scanf("%f", &interest_rate);

  printf("Enter montly payment: ");
  scanf("%f", &monthly_payment);

  printf("%.2f, %.2f, %.2f\n", loan, interest_rate, monthly_payment);

  // Assuming that interest_rate is 6.0f
  interest_rate = interest_rate / 12.0f;    // 0.5f
  interest_rate = interest_rate / 100.0f;   // 0.005f

  printf("%.2f, %.3f, %.2f\n", loan, interest_rate, monthly_payment);

  loan = loan + loan * interest_rate; 
  loan = loan - monthly_payment;
  printf("Balance remaining after first payment: $%.2f\n", loan);

  loan = loan + loan * interest_rate; 
  loan = loan - monthly_payment;
  printf("Balance remaining after second payment: $%.2f\n", loan);

  loan = loan + loan * interest_rate; 
  loan = loan - monthly_payment;
  printf("Balance remaining after third payment: $%.2f\n", loan);

  return 0;
}
