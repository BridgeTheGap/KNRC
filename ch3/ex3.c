#include <stdio.h>

#define MAX 1024
#define NUMERIC 0
#define UPPER 1
#define LOWER 2

int set(char c1, char c2);
void expand(char s1[], char s2[]);

int main() {
    int c, i;
    char s[MAX], t[MAX];

    i = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            s[i] = '\0';
            expand(s, t);
            printf("%s\n", t);

            i = 0;
        } else {
            s[i++] = c;
        }
    }

    return 0;
}

/* set:  returns set type if c1 and c2 are a valid set and both belong to the same set */
int set(char c1, char c2) {
    if ((c1 >= '0' && c1 <= '9') && (c2 >= '0' && c2 <= '9')) {
        return NUMERIC;
    } else if ((c1 >= 'A' && c1 <= 'Z') && (c2 >= 'A' && c2 <= 'Z')) {
        return UPPER;
    } else if ((c1 >= 'a' && c1 <= 'z') && (c2 >= 'a' && c2 <= 'z')) {
        return LOWER;
    }

    return -1;
}

void expand(char s1[], char s2[]) {
    int i, j;
    
    for (i = j = 0; s1[i] != '\0'; i++) {
        if (i > 1 && s1[i-1] == '-' && set(s1[i], s1[i-2]) != -1 && s1[i] > s1[i-2]) {
            for (int k = 0; k < s1[i] - s1[i-2] - 1; k++) {
                s2[j++] = s1[i-2] + k+1;
            }
        } else if (i > 0) {
            s2[j++] = s1[i-1];
        }
    }
    
    if (i > 0) {
        s2[j++] = s1[i-1];
    }
    
    s2[j] = '\0';
}