#include <string.h>

/* reverse:  reverse string s in place */
void reverse(char s[]) {
    static int i;
    int c, j;

    j = strlen(s)-i-1;

    if (i < j) {
        c = s[i],  s[i] = s[j], s[j] = c;
        i++;
        reverse(s);
    } else {
        i = 0;
    }
}

// #include <stdio.h>

// int main() {
//     char s[] = "hello, world";
//     reverse(s);
//     printf("%s\n", s);
//     reverse(s);
//     printf("%s\n", s);

//     return 0;
// }
