#include <stdio.h>

#define SIZE 50
#define MAX_INPUT 49

int main (void)
{
  char text[SIZE];
  char text_copy[SIZE];
  char search;
  int total = 0, spaces = 0, digits = 0, upper = 0, lower = 0, found = 0;
  int i;

  // Read the sentence; an empty line is rejected and asked again.
  // // Anything past 49 characters is silently discarded.
  do
  {
    text[0] = '\0';
    printf("Enter a sentence: ");
    scanf("%49[^\n]", text);
    while (getchar() != '\n');

    if (text[0] == '\0')
    {
      printf("Invalid input. The sentence can't be empty.\n");
    }
  } while (text[0] == '\0');

  printf("\nText: %s\n\n", text);

  // Count the chracters and classify each one
  for (i = 0; text[i] != '\0'; i++)
  {
    total++;

    if (text[i] == 32)
    {
      spaces++;
      continue;
    }

    if (text[i] >= 48 && text[i] < 57)
    {
      digits++;
      continue;
    }

    if (text[i] >= 65 && text[i] <= 90)
    {
      upper++;
      continue;
    }

    if (text[i] >= 97 && text[i] <= 122)
    {
      lower++;
    }
  }

  printf("Characters: %d\n", total);
  printf("Spaces: %d\n", spaces);
  printf("Digits: %d\n", digits);
  printf("Uppercase: %d\n", upper);
  printf("Lowercase: %d\n\n", lower);

  printf("First Character: %c\n", text[0]);
  printf("Last Character: %c\n\n", text[total - 1]);

  // Read the search character; only the first character typed is used
  // Valid: space, digits, uppercase or lowercase letters
  do {
    printf("Enter a character to search for: ");
    scanf("%c", &search);
    if (search != '\n') while(getchar() != '\n');

    if (search == 32 || (search >= 48 && search <= 57) || (search >= 65 && search <= 90) || (search >= 97 && search <= 122)) break;

    printf("Invalid character. Use a letter, digit or space.\n");
  } while(1);

  for (i = 0; text[i] != '\0'; i++)
  {
    if (text[i] == search) found++;
  }

  if (found == 0) printf("'%c' doesn't appear at all.\n\n", search);
  else if (found == 1) printf("'%c' appears 1 time.\n\n", search);
  else printf("'%c' appears %d times.\n\n", search, found);

  // Copy the text, then terminate the copy
  i = 0;
  while (text[i] != '\0')
  {
    text_copy[i] = text[i];
    i++;
  }
  text_copy[i] = '\0';

  printf("Copy: ");
  for (i = 0; text_copy[i] != '\0'; i++) printf("%c", text_copy[i]);
  printf("\n");

  return 0;
}
