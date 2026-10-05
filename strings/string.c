#include <stdio.h>

int main(void)
{
  char s[] = "Hello, world!\n";

  printf("%s", s);
  printf("%c\n", *s);

  s[0] = 'B';
  printf("%s", s);

  char *x = "Hello, world!\n";
  x = "Hello\n";
  printf("%s", x);

  return 0;
}
