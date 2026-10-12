#include <stdio.h>

#define PI 3.14

int main(void)
{
  int radius = 10;
  float volume;

  volume = 4.0f / 3.0f * PI * radius * radius * radius;

  printf("The volume of a sphere with radius %d is %.2f\n", radius, volume);

  return 0;
}
