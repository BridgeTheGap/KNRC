#include <stdio.h>

int main() {
    int i, c, lim;
    lim = 1000;

    char s[lim];

    for (i=0; i<lim - 1 && (c=getchar()) != '\n' && c != EOF; ++i) {
        s[i] = c;
    }

    /*
    i = 0;
    while (i < lim-1) {
        if ((c = getchar()) != '\n') {
            if (c != EOF) {
                s[i] = c;
                ++i;
            }
        }
    }
    */

    s[i] = '\0';
}