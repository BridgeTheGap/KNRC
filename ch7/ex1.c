#include <stdio.h>
#include <ctype.h>

int cmdcmp(char *, char *);

int main(int argc, char *argv[]) {
    int c;
    int (*f)(int);
    if (cmdcmp(argv[0], "lower") == 0) {
        f = tolower;
    } else if (cmdcmp(argv[0], "upper") == 0) {
        f = toupper;
    } else {
        printf("Error: change program name to \"lower\" or \"upper\"\n");
        return 0;
    }

    while ((c = getchar()) != EOF) {
        putchar(f(c));
    }
    return 0;
}

#include <string.h>

int cmdcmp(char *lhs, char *rhs) {
    while (*lhs == '.' || *lhs == '/') {
        lhs++;
    }
    while (*rhs == '.' || *rhs == '/') {
        rhs++;
    }
    return strcmp(lhs, rhs);
}