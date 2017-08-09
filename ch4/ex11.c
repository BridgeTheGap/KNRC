#include <stdio.h>
#include <ctype.h>

#include "calc.h"

/* getop:  get next operator or numeric operand */
int getop(char s[]) {
    int i, c;
    static int last = '\0';
    while ((s[0] = c = last == '\0' ? getch() : last) == ' ' || c == '\t') { }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c;    /* not a number */
    }
    i = 0;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch())) { }
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getch())) { }
    }
    s[i] = '\0';
    if (c != EOF) {
        last = c;
    }
    return NUMBER;
}
