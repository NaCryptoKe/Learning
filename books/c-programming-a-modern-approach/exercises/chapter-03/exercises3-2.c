/*
 * Write calls of printf that display a float variable x in the following formats
 * (a) Exponential notation; left-justified in a field of size 8; one digit after the decimal point.
 * (b) Exponential notation; right-justified in a field of size 10; six digits after the decimal point.
 * (c) Fixed decimal notation; left-justified in a field of size 8; three digits after the decimal point.
 * (d) Fixed decimal notation; right-justified in a field of size 6; no digits after the decimal point.
*/

#include <stdio.h>

int main(void)
{
    float x = 15.678;

    /*
     * - forces left-justification
     * 8 sets the minimum field size
     * .1 specifies on digit after the decimal point
     * e selects exponential notation
     */
    printf("%-8.1e\n", x);

    /*
     * right-justification is by default
     * 10 sets the minimum field
     * .6 specifies six digit after the decimal point
     * e selects exponential notation
     */
    printf("%10.6e\n", x);

    /*
     * - left justified
     * 8 sets the minimum field
     * .3 tells 3 digits after decimal
     *  f selects fixed decimal notation
     */
    printf("%-8.3f\n", x);

    /*
     * right justfied by default
     * 6 sets the minimum field size
     * .0 specifies zero digits after the decimal point
     * f selects fixed decimal notation
     */
    printf("%6.0f\n", x);
    return 0;
}
