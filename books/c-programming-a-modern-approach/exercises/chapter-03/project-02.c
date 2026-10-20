#include <stdio.h>

int main(void)
{
    int item_number, day, month, year;
    float unit_price;

    printf("Enter item number: ");
    scanf("%d", &item_number);

    printf("Enter unit price: ");
    scanf("%f", &unit_price);

    printf("Enter purchase date: ");
    scanf("%d/%d/%d", &month, &day, &year);

    printf("Item\t\tUnit\t\tPurchase\n");
    printf("\t\tPrice\t\tDate\n");
    printf("%-d\t\t$%7.2f\t\t%-2d/%-d/%-4d\n", item_number, unit_price, month, day, year);

    return 0;
}
