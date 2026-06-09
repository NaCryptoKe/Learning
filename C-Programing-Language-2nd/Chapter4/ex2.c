#include <stdio.h>

double atof (char s[]);

int main(void) {
    char s[100] = "-3.-14";
    printf ("%f\n", atof(s));
}

double atof (char s[]) {
    double value = 0;
    double sign = 1;   // 1 for positive and -1 for negative
    int is_decimal = 0; // 1 is decimal and 0 is not
    double divider = 10;
    for (int i = 0; s[i] != '\0'; i++) {    // a manual way of doing strlen()
       if (s[i] == ' ') continue;
       if (s[i] == '-') {
           sign *= -1;
           continue;
       }
       if (s[i] == '.'){
           is_decimal = 1;
           continue;
       }

       if (!is_decimal) {
            if (s[i] >= '0' && s[i] <= '9') {
                value = value * 10 + (s[i] - '0');
            } else {
                printf ("Only digits allowed");
                return -1;
            }
       } else {
            if (s[i] >= '0' && s[i] <= '9') {
                value = value + (s[i] - '0')/divider;
                divider *= 10;
            } else {
                printf ("Only digits allowed");
                return -1;
            }
       }
    }
    return value * sign;
}
