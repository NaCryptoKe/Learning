#include <stdio.h>

void fill_stack(void)
{
  int junk[5] = {111, 222, 333, 444, 555};
  (void)junk;
}

void show_uninitialized(void)
{
  int mystery[5];
  for (int i = 0; i < 5; i++)
       printf("%d\n", mystery[i]);
}

int main(void)
{
  fill_stack();
  show_uninitialized();
  return 0;
}
