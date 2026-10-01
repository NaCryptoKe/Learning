#include <stdio.h>
int global_init = 42;
int global_uninit;

int main(void) {
  static int static_local = 7;
  int auto_local = 3;
  printf("global_init: %p\n", (void *)&global_init);
  printf("global_uninit: %p\n", (void *)&global_uninit);
  printf("static_local: %p\n", (void *)&static_local);
  printf("auto_local: %p\n", (void *)&auto_local);

  return 0;
}
