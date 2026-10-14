# Chapter 3: Formatted Input/Output

## `printf` Function

printf follows a multi-argument function.

```c
printf(string, expr1, expr2, ...);
```

The `%` is a conversion specification.

> [!Example]

```c
// Prints int and float values in various formats

#include <stdio.h>

int main(void)
{
  int i;
  float x;

  i = 40;
  x = 839.21f;

  printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
  printf("|%10.3f|%10.3e|%-10g|\n", x, x, x);

  return 0;
}
```

### Escape Sequences

an escape sequence is when we use '\' to make the string behave how we want them.

- Alert (bell)    \a
- Backspace       \b
- New line        \n
- Horizontal tab  \t
- Forward diagonal  \ \
- double quote    \ "

## `scanf` Function

Reads input according to a particular format.

```c
int i, j;
float x, y;

scanf("%d%d%f%f", &i, &j, &x, &y);
```


