#include <stdio.h>

#define MAX 1000

int trimstr(char str[]);

int main() {
    int len;
    char line[MAX];

    while ((len = trimstr(line)) > 0) {
        printf("%d %s", len, line);
    }

    return 0;
}

/* trimstr: read a line into `str`, return last character index */

int trimstr(char str[]) {
    int c, e;

    for (int i = e = 0; i < MAX-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        if (c != ' ' && c != '\t') {
            e = i+1;
        }
        str[i] = c;
    }

    if (c == '\n') {
        str[e] = '\n';
        ++e;
    }
    str[e] = '\0';

    return e;
}