#include <stdio.h>

#define TAB 8

void entab(void);

int main() {
    entab();

    return 0;
}

void entab(void) {
    // 1. Index char
    // 2. If char == ' ', count nspace
    // 3. Else, print
    // 4. If nspace > 0 && char != ' ' && i / TAB > (i-nspace) / TAB, ntab = (i / TAB) - ((i-nspace) / TAB)
    //        print ntab tabs
    //        print ' ' for remainder 
    // 5. Else, print ' ' for nspace

    int c, i, nspace;
    i = nspace = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++nspace;
            ++i;
        } else if (c == '\t') {
            int a = i/TAB;
            int remainder = i - TAB * a;
            int padding = TAB - remainder;

            nspace = nspace + padding;
            i = i + padding;
        } else {
            if (nspace > 0) {
                int curr = i / TAB;
                int prev = (i-nspace) / TAB;

                if (curr > prev) {
                    for (int j = 0; j < curr - prev; ++j) {
                       putchar('\t');
                    }

                    for (int j = 0; j < i - TAB * curr; ++j) {
                        putchar(' ');
                    }
                } else {
                    for (int j = 0; j < nspace; ++j) {
                        putchar(' ');
                    }
                }

                nspace = 0;
            } 

            putchar(c);

            if (c == '\n') {
                i = 0;
                nspace = 0;
            } else {
                ++i;            
            }
        }
    }
}
