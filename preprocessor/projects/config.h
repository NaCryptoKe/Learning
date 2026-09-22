#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

#define DEBUG 1

#if DEBUG == 1
  #define debug_print(msg) printf(msg)
#else
  #define debug_print(msg)
#endif // DEBUG == 1

#define VERSION 2

#define SQUARE(x) ((x) * (x)) // doesn't guarantee to work properly for preincrement, predecrement, postincrement and postdecrement

#define MAX_ITEMS 10

extern int items[MAX_ITEMS];

#endif // CONFIG_H
