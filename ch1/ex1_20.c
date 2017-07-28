#include <stdio.h>

#define TAB 8

void detab(void);

int main() {
    detab();

    return 0;
}

void detab(void) {
    int c, i;
    i = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int a = i/TAB;
            int remainder = i - TAB * a;
            int padding = TAB - remainder;
            
            for (int j = 0; j < padding; ++j) {
                putchar(' ');
            }

            i = i + padding;
        } else {
            putchar(c);

            if (c == '\n') {
                i = 0;
            } else {
                ++i;
            }
        }
    }
}
