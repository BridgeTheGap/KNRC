/* _strncpy */
char *_strncpy(char *s, char *ct, int n) {
    int i;
    for (i = 0; i < n && (*(s+i) = *(ct+i)) != '\0'; i++) { }
    while (i < n) {
        *(s+i) = '\0';
        i++;
    }
    *(s+i) = '\0';
    return s;
}

/* _strncat */
char *_strncat(char *s, char *ct, int n) {
    int i, j;
    for (i = 0; *(s+i) != '\0'; i++) { }
    for (j = 0; j < n && (*(s+i+j) = *(ct+j)) != '\0'; j++) { }
    while (j < n) {
        *(s+i+j) = '\0';
        j++;
    }
    *(s+i+j) = '\0';
    return s;
}

/* _strncmp */
int _strncmp(char *cs, char *ct, int n) {
    for (int i = 0; 
        i < n && *cs == *ct && *cs != '\0'; 
        i++, cs++, ct++) { }
    if (*cs == '\0') {
        return 0;
    } else {
        return *cs - *ct;
    }
}

#include <stdio.h>

int main() {
    char s[14] = "hello, ";
    char *t = "world";

    printf("s = %s\n", _strncat(s, t, 1));
    _strncpy(s, "hello, ", 7);
    printf("s = %s\n", _strncat(s, t, 2));
    _strncpy(s, "hello, ", 7);
    printf("s = %s\n", _strncat(s, t, 3));
    _strncpy(s, "hello, ", 7);
    printf("s = %s\n", _strncat(s, t, 4));
    _strncpy(s, "hello, ", 7);
    printf("s = %s\n", _strncat(s, t, 5));
    _strncpy(s, "hello, ", 7);
    printf("s = %s\n", _strncat(s, t, 6));

    printf("s = %s\n", _strncpy(s, t, 6));
    printf("s = %s\n", _strncpy(s, t, 5));
    printf("s = %s\n", _strncpy(s, t, 4));
    printf("s = %s\n", _strncpy(s, t, 3));
    printf("s = %s\n", _strncpy(s, t, 2));
    printf("s = %s\n", _strncpy(s, t, 1));

    char *cs = "same, diff";
    char *ct = "same, ffid";

    for (int i = 0; i < 10; i++) {
        printf("(\"%s\", \"%s\", %d) => %d\n", cs, ct, i+1, _strncmp(cs, ct, i+1));
        printf("(\"%s\", \"%s\", %d) => %d\n", ct, cs, i+1, _strncmp(ct, cs, i+1));
        printf("(\"%s\", \"%s\", %d) => %d\n", cs, ct, i+1, _strncmp(ct, ct, i+1));
        printf("\n");
    }

    return 0;
}
