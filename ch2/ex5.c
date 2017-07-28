#include <stdio.h>

#define MAX 1000

int any(char s1[], char s2[]);

int main() {
    int curr = 0;
    int c, i;
    char s1[MAX];
    char s2[MAX];

    i = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n') {
            if (curr == 0) {
                s1[i] = '\0';
                i = 0;
                curr++;
            } else {
                s2[i] = '\0';
                i = 0;
                curr = 0;
                
                printf("s1: %s; s2: %s\n", s1, s2);
                printf("-> %d\n", any(s1, s2));
            }
        } else {
            if (curr == 0) {
                s1[i++] = c;
            } else {
                s2[i++] = c;
            }
        }
    }

    return 0;
}

int any(char s1[], char s2[]) {
    for (int i = 0; s1[i] != '\0'; i++) {
        for (int j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }

    return -1;
}