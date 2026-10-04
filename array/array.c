#include <stdio.h>

int main(void)
{
  // Not a proper way of doing an array
  // but it works the same way as it if you want to use it.
  int i = 3, j = 4;
  int *p = &i;

  printf("Memory: i -> %p, j -> %p\n", &i, &j);
  printf("arr[0]: %d\n", *p);
  printf("arr[1]: %d\n", *p+1);

  // Actual array
  int arr[2] = {3, 4};
  int x = 5;
  printf("arr[0]: %d\n", arr[0]);
  printf("arr[1]: %d\n", arr[1]);
  printf("arr[2]: %d\n", *arr+2);


  // TRYING OUT
  printf("==== TRYING OUT ====\n");
  int values[7] = {55, 11, [5]1,2};

  for (int a = 0; a < 7; a++)
  {
    printf("arr[%d]: %d\n", a, values[a]);
  }

  printf("==== TRYING OUT END ====\n");

  int b[2][3] = {{1, 2, 3}, {4, 5, 6}};
  printf("b[4]: %d\n", &b[4]);
  return 0;
}
