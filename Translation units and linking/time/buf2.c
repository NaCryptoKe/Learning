#include "buffer.h"
#include <stdio.h>

int buffer_size = 64;

int main(void) {
  printf("%d\n", buffer_size);
  reset_buffer();
  printf("%d\n", buffer_size);

  return 0;
}
