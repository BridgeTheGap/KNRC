#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop:  get next operator or numeric operand */
int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t') { }
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
    if (c != EOF) {
        s[i] = '\0';
        ungetch(c);
    } else {
        s[i-1] = '\0';
    }
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];   /* buffer for ungetch */
int  bufp = 0;       /* next free position in buf */

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}