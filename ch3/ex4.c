#include <stdio.h>
#include <limits.h>

void reverse(char s[]);
void itoa(int n, char s[]);

int main() {
    char s[1024];
    itoa(INT_MIN, s);
    printf("%s\n", s);

    return 0;    
}

void itoa(int n, char s[]) {
    int i, sign;
    sign = n < 0 ? -1 : 1;
    i = 0;
    do {
        s[i++] = sign >= 0 ?
            n % 10 + '0' : 
            -(n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}