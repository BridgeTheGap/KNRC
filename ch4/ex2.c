#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

int main() {
    int c, i;
    char s[1024];
    
    i = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            s[i] = '\0';
            i = 0;
            printf("atof = %f\n", atof(s));
        } else {
            s[i++] = c;
        }
    }
}

/* atof:  convert string s to double */
double atof(char s[]) {
    double val, power;
    int i, sign;
    int e, esign;

    for (i = 0; isspace(s[i]); i++) { } /* skip white space */

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.') {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i++] == 'e') {
        if (s[i] == '-') {
            i++;
            esign = -1;
        } else {
            esign = 1;
        }

        for (e = 0; s[i] != '\0'; i++) {
            e = 10 * e + (s[i] - '0');
        }
        
        if (esign > 0) {
            for (int j = 0; j < e; j++) {
                power /= 10.0;
            }
        } else {
            for (int j = 0; j < e; j++) {
                power *= 10.0;
            }
        }
    }

    return sign * val / power;
}