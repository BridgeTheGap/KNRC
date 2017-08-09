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

char buf = '\0';

int getch(void) {
    return buf > '\0' ? buf : getchar();
}

void ungetch(int c) {
    buf = c;
}
