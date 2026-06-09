#include <stdio.h>

int strindex(char s[], char t[]);

int main(void) {
    char s[] = "could would should";
    char t[] = "ould";
    printf("%d\n", strindex(s, t)); /* should print 14 */
    return 0;
}

int strindex(char s[], char t[]) {
    int i, j, k;
    int last = -1;  /* store the last (rightmost) match */

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            last = i;  /* found a match, keep going */
    }
    return last;
}
