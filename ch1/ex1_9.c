#include <stdio.h>

int main() {

    int c, bc;
    
    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            bc = 0;
            putchar(c);
        } else {
            if (++bc == 1) {
                putchar(c);
            }
        }
    }

}