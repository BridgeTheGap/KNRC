/* strcat:  copies t to the end of s */
void _strcat(char *s, char *t) {
    while (*s != '\0') { 
        s++;
    }
    while ((*s++ = *t++) != '\0') { }
}

#include <stdio.h>
int main() {
    char s[13] = "hello, ";
    char *t = "world";
    
    _strcat(s, t);
    printf("%s\n", s);
    return 0;
}