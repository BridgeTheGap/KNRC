/* itoa:  convert n to characters in s */
void itoa(int n, char s[]) {
    static int i;
    static int sign;

    if (sign == 0 && (sign = n) < 0) {
        n = -n;
    }

    if (n/10) {
        itoa(n/10, s);
    }    
    
    if (i == 0 && sign < 0) {
        s[i++] = '-';
    }

    s[i++] = n % 10 + '0';
    
    if ((sign < 0 ? -sign : sign) == n) {
        s[i] = '\0';
    }
}

// #include <stdio.h>

// int main() {
//     char s[10];
//     itoa(-1024, s);
//     printf("s = %s\n", s);
//     return 0;
// }
