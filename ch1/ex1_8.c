#include <stdio.h>

int main() {

    int c;
    long nb, nt, nl;

    nb = 0;
    nt = 0;
    nl = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') { ++nb; }
        if (c == '\t') { ++nt; }
        if (c == '\n') { ++nl; }
    }

    printf("Blank: %d; Tab: %d; New line: %d\n", nb, nt, nl);

}