#include <stdio.h>

#define SET_COUNT 36

void reverse(char s[]);
void itob(int n, char s[], int b);

int main() {
    char s[1024];
    int n = -45600;
    int b = 16;
    itob(n, s, b);
    printf("n = %d; b = %d\n%s\n", n, b, s);

    return 0;
}

void itob(int n, char s[], int b) {
    static const char charset[SET_COUNT] = "0123456789ABCDEFGHIJKLMOPQRSTUVWXYZ";
    
    if (b > SET_COUNT) { return; }

    int i, sign;
    i = 0;
    sign = n < 0 ? -1 : 1;

    do {
        s[i++] = charset[n%b > 0 ? n%b : -(n%b)];
    } while ((n /= b) != 0);

    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';

    reverse(s);
}