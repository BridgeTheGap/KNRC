#include <stdio.h>

extern int max;

void squeeze(char s1[], char s2[]);

int main() {
    int max = 1000;
    int curr = 0;
    int c, i;
    char s1[max];
    char s2[max];

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
                squeeze(s1, s2);
                printf("-> %s\n", s1);
            }
        } else {
            if (curr == 0) {
                s1[i++] = c;
            } else {
                s2[i++] = c;
            }
        }
    }
}

/* squeeze: delete all s2 from s1 */

void squeeze(char s1[], char s2[]) {
    int c, i, j;
    i = j = 0;

    while ((c = s1[i++]) != '\0') {
        int add = 1;

        for (int k = 0; s2[k] != '\0'; k++) {
            if (c == s2[k]) {
                add = 0;
            }
        }

        if (add) {
            s1[j++] = c;
        }
    }

    s1[j] = '\0';
}