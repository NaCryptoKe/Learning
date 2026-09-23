#include <stdio.h>
#define LOG(fmt, ...) fprintf(stderr, "[%s: %d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

int main(void)
{
  LOG("test");
  return 0;
}

