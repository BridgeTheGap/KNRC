/* strend:  returns 1 if t occurs at the end of s */
int strend(char *s, char *t) {
    int i;
    
    for (i = 0; *(t+i) != '\0'; i++) { }

    while (*s != '\0') {
        s++;
    }
    
    s -= i;
    
    while (*s == *t) {
        if (*s == '\0') {
            return 1;
        }
        s++;
        t++;
    }
    return 0;
}

#include <stdio.h>

int main() {
    printf("hello, llo => %d\n", strend("hello", "llo"));
    printf("hello, lo  => %d\n", strend("hello", "lo"));
    printf("hello, o   => %d\n", strend("hello", "o"));
    printf("hello, ol  => %d\n", strend("hello", "ol"));
    printf("hello, el  => %d\n", strend("hello", "el"));
    return 0;
}