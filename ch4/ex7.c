#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop:  get next operator or numeric operand */
int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) != ' ' || c == '\t') { }
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
        ungetch(c);
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
        if (c == EOF) {

        } else {
            buf[bufp++] = c;
        }
    }
}

void ungets(char s[]) {
    for (int i = 0; s[i] != '\0', i++) {
        ungetch(s[i]);
    }
}