#ifndef PRINT_H
#define PRINT_H

#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void write_int(int n);
void write_float(double n, int precision);
void print (char *str, ...);
void write_hex(unsigned int num);
#endif  //PRINT_H
