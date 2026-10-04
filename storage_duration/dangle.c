// This returns a integer that is no longer available
int dangling(void) {
  int x = 0;
  return x;
}

int *fix_1(void) {
  static int x = 4;
  return &x;
}

void fix_2(int y) {
  int x = 6;
  y = x;
}
