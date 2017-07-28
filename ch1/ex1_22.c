#include <stdio.h>

#define MAXWIDTH 80
#define TAB      8

void fold(void);

int main() {
    fold();

    return 0;
}

void fold(void) {
    int c, i, nspace;

    i = nspace = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++nspace;
            ++i;
        } else if (c == '\n') {
            putchar(c);
            i = nspace = 0;
        } else if (c == '\t') {
            int a = i/TAB;
            int remainder = i - TAB * a;
            int padding = TAB - remainder;

            nspace = nspace + padding;
            i = i + padding;
        } else {
            if (i < MAXWIDTH) {
                for (; nspace > 0; --nspace) {
                    putchar(' ');
                }
                putchar(c);
                ++i;
            } else {
                printf("\n%c", c);
                
                i = 1;
                nspace = 0;
            }
        }
    }
}