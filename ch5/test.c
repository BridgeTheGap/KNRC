#include <stdio.h>

void _print(char *);

int main() {
    _print("hello, world");
    
    return 0;
}

void _print(char *s) {
    int c, i;
    for (i = 0; (c = *(s+i)) != '\0'; i++) {
        putchar(c);
    }
    putchar('\n');
}