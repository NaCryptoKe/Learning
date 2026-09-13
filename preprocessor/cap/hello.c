#include <stdio.h>

#define FOO "FOO\n"

#define HELLO(name) printf("HELLO" name)

#ifdef FOO
printf("\n\n====FOO HAS BEEN DECLARED====\n\n");
#endif

int main(void)
{
  HELLO(FOO);
}
