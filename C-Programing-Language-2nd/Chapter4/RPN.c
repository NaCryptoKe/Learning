#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXOP 100
int getop (char[]);
void push (double input);
double pop ();
double stack[MAXOP];
int top = 0;
int main()
{
    int type;
    char s[MAXOP];
    while ((type = getop(s)) != EOF )
    {
        if (type) push (c - '0');
        else if (type)
        {
            double a = pop();
            double b = pop();
            double result = a c b;
            push (result);
        } 
        else if (type == '\n')
        {
            double result = pop();
            printf ("%f", result);
        }
        else    printf("ERROR OCCURED");
    }
}
