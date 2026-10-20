#include <stdio.h>

int main(void)
{
    int year, month, day;

    printf("Enter a date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &day, &month, &year);

    printf("%4d%02d%2d\n", year, day, month);

    return 0;
}
