#include <stdio.h>
#include "tiny.h"
// Attempting helper() from tiny_run.c fails at the linking stage with an "undefined reference to 'helper'" error 
// because internal linkage (static) restricts the symbol's visibility strictly to tiny.c.
static void helper(void) { printf("Hello from static helper function"); }

void public_feature(void) {
  helper();
}
