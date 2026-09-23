#include <stdio.h>

#define REGISTER(type, name)  \
        type name;            \
        type get_##name(void) \
        { return name; }      \
        void set_##name(type v) \
        { name = v; }

REGISTER(int, score);

int main(void)
{
  set_score(42);
  printf("%d\n", get_score());

  return 0;
}
