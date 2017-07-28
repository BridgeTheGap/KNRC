#include <stdio.h>

extern int max;

int htoi(char s[]);

int main() {
    int max = 1000;
    int c, i;
    i = 0;
    char l[max];

    while ((c = getchar()) != EOF) {
        if (c != '\n') {
            if ((i == 0 && c == '0') || 
                (i == 0 && c == 'x') ||
                (i == 0 && c == 'X')) {
                
            } else {
                l[i] = c;
                ++i;
            }
        } else {
            l[i] = '\0';
            printf("Hex: 0x%s = %d\n", l, htoi(l));
            i = 0;
        }
    }
}

int htoi(char s[]) {
    int i, n;
    i = n = 0;

    while (s[i] != '\0')  {
        if (s[i] >= '0' && s[i] <= '9') {
            n = n * 16 + s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            n = n * 16 + (s[i] - 'a' + 10);
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            n = n * 16 + (s[i] - 'A' + 10);
        }
        ++i;
    }

    return n;
}