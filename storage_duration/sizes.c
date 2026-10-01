#include <stdio.h>
#include <limits.h>

int main(void)
{
  printf("char:\t%zu\n", sizeof(char));
  printf("short:\t%zu\n", sizeof(short));
  printf("int:\t%zu\n", sizeof(int));
  printf("long:\t%zu\n", sizeof(long));
  printf("long long:\t%zu\n", sizeof(long long));
  printf("float:\t%zu\n", sizeof(float));
  printf("double:\t%zu\n", sizeof(double));
  printf("int*:\t%zu\n", sizeof(int*));
  printf("char*:\t%zu\n", sizeof(char*));
  printf("CHAR_MIN:\t%d\n", CHAR_MIN);
  printf("CHAR_MAX:\t%d\n", CHAR_MAX);
  return 0;
}
