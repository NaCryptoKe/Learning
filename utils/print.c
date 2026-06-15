#include "print.h"

void write_char(char c) {
    write (1, &c, 1);
}

void write_hex(unsigned int num){
    char hex_digits[] = "0123456789abcdef";

    char buffer[9];
    int i = 0;

    if (num == 0) {
        write_char('0');
        return;
    }

    while (num > 0) {
        buffer[i] = hex_digits[num%16];
        num /= 16;
        i++;
    }

    while(i > 0) {
        i--;
        write_char(buffer[i]);
    }
}

void write_int(int n) {
    if (n < 0) {
        write(1, "-", 1);
        n *= -1;
    }
    char buf[12];
    int i = 11;
    if (n == 0) { write(1, "0", 1); return; }
    while (n > 0) {
        buf[--i] = '0' + (n % 10);
        n /= 10;
    }
    write(1, buf + i, 11 - i);
}

void write_float(double num, int precision) {
    if (num < 0) {
        write(1, "-", 1);
        num = -num;
    }
    
    long long whole_part = (long long) num;
    write_int(whole_part);

    if (precision > 0) {
        write(1, ".", 1);

        double fractional_part = num - (double)whole_part;

       for (int i = 0; i < precision; i++) {
           fractional_part *= 10;
           int digit = (int)fractional_part;
           write_int(digit);
           fractional_part -= digit;
       } 
    }

}

void print(char *str, ...) {
    int per_sign = 0;
    if (str == NULL) return;

    char *ptr = str;
    va_list args;
    va_start(args, str);

    while (*ptr != '\0') {
        char ch = *ptr;

        if (ch == '%' && !per_sign) {
            ptr++;
            per_sign = 1;
            continue;
        }

        if (per_sign) {
            ptr++;
            per_sign = 0;
            if (ch == '%')  write(1, &ch, 1);
            else if (ch == 'd') {
                int num = va_arg(args, int);
                write_int(num);
            } else if (ch == 'f') {
                double num = va_arg(args, double);
                write_float(num, 15);
            } else if (ch == 'c') {
                char c = (char)va_arg(args, int);
                write (1, &c, 1);
            } else if (ch == 's') {
                char *new_str = va_arg(args, char *);
                int len = 0;
                while (new_str[len]) len++;
                write(1, new_str, len);
            } else if (ch == 'x') {
                int hex = va_arg(args, unsigned int);
                write_hex(hex);
            } else {
                write(2, "Invalid Usage\n", 14);
                return;
            }
            continue;
        }

        write(1, &ch, 1);
        
        ptr++;
    }

    va_end(args);
}
