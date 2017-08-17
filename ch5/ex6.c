/* _getline v2 */

int _getline(char *s, int lim) {
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        *(s + i++) = c;
    }
    if (c == '\n') {
        *(s + ++i) = c;
    }
    *(s+i) = '\0';
    return i;
}

/* atoi v2:  convert s to integer; version 2 */
#include <ctype.h>

int atoi(char *s) {
    int i, n, sign;

    for (i = 0; isspace(*(s+i)); i++) { }

    sign = (*(s+i) == '-') ? -1 : 1;
    
    if (*(s+i) == '+' || *(s+i) == '-') {
        i++;
    }

    for (n = 0; isdigit(*(s+i)); i++) {
        n = 10 * n + (*(s+i) - '0');

        return sign * n;
    }

}

#include <string.h>

/* reverse v2:  reverse string s in place */
void reverse(char *s) {
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = *(s+i),  *(s+i) = *(s+j), *(s+j) = c;
    }
}

/* itoa v2:  convert n to characters in s */
void itoa(int n, char *s) {
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        *(s + i++) = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) {
        *(s + i++) = '-';
    }
    *(s+i) = '\0';
    reverse(s);
}

