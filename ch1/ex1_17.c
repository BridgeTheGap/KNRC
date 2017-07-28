#include <stdio.h>

#define MAX 1000
#define MIN 80

int getstr(char str[]);

int main() {
    int  len;
    char line[MAX];

    while ((len = getstr(line)) > 0) {
        if (len > MIN) {
            printf("%d %s", len, line);
        }
    }
}

int getstr(char str[]) {
    int i, c;
    for (i = 0; i < MAX-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        str[i] = c;
    }

    if (c == '\n') {
        str[i] = '\n';
        ++i;
    }
    str[i] = '\0';

    return i;
}