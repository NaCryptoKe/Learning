#include <stdio.h>

// Pass by value
int *increment_v (int a)
{
  // Here we aren't passing a memory address,
  // rather a copy of the variable we passed.
  // So, lets assume we passed 
  // int a; which has a memory of 0x7ffc4443122c
  // but the memory of the a within the function maybe 0x7ffc444311fc, 
  // making it to different variables rather than one.
  a++;
  int *b = &a;
  printf("WITHIN PASS BY VALUE =>\n\taddress: %p\n\tvalue: %d\n", b, a);

  return b;
}

// Pass by pointer
void increment_p (int *p)
{
  *p = *p + 1;
  printf("WITHIN PASS BY POINTER =>\n\taddress: %p\n\tvalue: %d\n", p, *p);
}

int main(void) {
  int a = 10;
  int *b = &a;

  printf("BEFORE =>\n\taddress: %p\n\tvalue: %d\n", b, a);

  int *c = increment_v(a);

  printf("AFTER VALUE =>\n\taddress: %p\n\tvalue: %d\n", b, a);

  printf("AFTER VALUE FALSE MEMORY =>\n\taddress: %p\n\tvalue: %d\n", c, *c);

  increment_p(b);

  printf("AFTER POINTER =>\n\taddress: %p\n\tvalue: %d\n", b, a);

  return 0;
}
