#include <stdio.h>

#define MAX 1000

int _getline(char s[]);
void reverse(char s[]);

int main() {
    char str[MAX];

    while (_getline(str) > 0) {
        reverse(str);
    }

    return 0;
}

int _getline(char s[]) {
    int i, c;

    for (i = 0; i < MAX-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}

void reverse(char s[]) {
    int i;
    for (i = 0; s[i] != '\0' && s[i] != '\n'; ++i) { }
    for (i = i-1; i >= 0; --i) {
        putchar(s[i]);
    }
    putchar('\n');
}