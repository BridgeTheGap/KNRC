#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getfloat:  get next float from input into *pn */
int getfloat(double *pn) {
    int c, sign;
    double d;

    while (isspace(c = getch())) { } /* skip white space */

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);    /* NAN */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        if (!isdigit(c = getch())) {
            ungetch(c);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }
    if (c == '.') {
        c = getch();
        d = 1.0;
        
        while (isdigit(c)) {
            *pn = 10 * *pn + (c - '0');
            d *= 10.0;
            c = getch();
        }

        *pn /= d;

        if (c != EOF) {
           ungetch(c);
        }
    } else if (c != EOF) {
        ungetch(c);
    }

    *pn *= sign;

    return c;
}

int main() {
    double f;

    while (getfloat(&f) > 0) {
        printf("%f\n", f);
    }

    return 0;
}