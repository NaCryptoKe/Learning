# Chapter 2: C Fundamentals

We try to print the bad pun, which is basically staiting:
`To C, or not to C: that is the question`

```c
#include <stdio.h>  // preprocessor directive

int main(void)
{
  printf("To C, or not to C: that is the question.\n");
  return 0;
}
```

## Compiling and Linking Process

- Preprocessing. resolving the preprocessor directives.
- Compiling. translating to machine instructions (object code). But it is not quite ready to run yet.
- Linking. a linker combines the object codes produced by the compiler with additional code needed.

## The GCC compiler

One of the most popular C compilers.

We can run pun.c to be turned into a program by doing:

`gcc -o pun pun.c`

## The general form of a simple program

```c
directives

int main (void)
{
  statements;
}
```

### Directives

This are commands intended for the preprocessor. More will be discussed in Chapters 14 and 15.

The `#include` directive simply includes another files contents to the file we are currently on.

## Comments

There are two type of comments in C:

- Inline comments (//) and
- Older style (/* ... */)

To make it stand out we will put `*` in new lines or make boxes out of them.

## Variables

Variables are storage locations that store values we set.

The follow the following type:

`type variable_name; // declaration`
`type variable_name = value; // declaration and assignment`

### Macro definitions

This is a way of using macros to store values on

```c
#define VARIABLE 5
```

### Identifiers

This is basically a name for the variable

Some use snake case and others use camel case, either is accepted here.

### Keywords

- auto
- break
- case
- char
- const
- continue
- default
- do
- double
- else
- enum
- extern
- float
- for
- goto
- if
- inline
- int
- long
- register
- restrict
- return
- short
- signed
- sizeof
- static
- struct
- switch
- typedef
- union
- unsigned
- void
- volatile
- while
- _Bool
- _Complex
- _Imaginary

