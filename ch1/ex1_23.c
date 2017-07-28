#include <stdio.h>

#define IN      1
#define OUT     0
#define NOPRINT -1

void removeComments(void);

int main() {
    removeComments();
}

void removeComments(void) {
    int c, prev, state, isInString;
    state = OUT;
    isInString = OUT;
    
    while ((c = getchar()) != EOF) {
        if (isInString == IN) {
            putchar(c);
            
            if (c == '"' && prev != '\\') {
                isInString = OUT;
            }
        } else {
            if (c == '/') {
                if (prev == '*') {
                    state = NOPRINT;
                }
            } else if (c == '*') {
                if (prev == '/') {
                    state = IN;
                } else if (state == OUT) {
                    putchar(c);
                }
            } else if (c == '"') {
                if (state != IN && prev != '\'') {
                    isInString = IN;
                    putchar(c);
                }
            } else {
                if (state != IN) {
                    if (state == NOPRINT) {
                        state = OUT;
                        prev = 0;
                    }

                    if (prev == '/') {
                        putchar(prev);    
                    }

                    putchar(c);
                }
            }
        }

        prev = c;
    }

    putchar('\n');
}