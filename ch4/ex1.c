#include <time.h>
#include <stdio.h>

#define MAXLINE 1000

int _getline(char s[], int lim);
int strrindex(char s[], char t[]);

char pattern[] = "ould";    /* pattern to search for */

/* find all lines matching pattern */
int main() {
    char line[MAXLINE];
    
    clock_t tic = clock();

    for (int i = 0; i < 1440000; i++) {
        if (strrindex("iiiii iiiii iiiii ould iiiii iiiii iiiii", pattern) < 0) {
            printf("error\n");
        }
    }

    clock_t toc = clock();

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    // while (_getline(line, MAXLINE) > 0 ) {
    //     int found = strrindex(line, pattern);
    //     if (found >= 0) {
    //         printf("Found \"%s\" at %d\n", pattern, found);
    //     }
    // }

    return 0;
}

/* strrindex:  returns the rightmost occurence of t in s */
int strrindex(char s[], char t[]) {
    int i, len, temp, value;

    value = -1;
    
    for (len = 0; t[len] != '\0'; len++) { }
    temp = len;
    
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == t[len - temp]) {
            if (--temp == 0) {
                value = i-len + 1;
                temp = len;
            }
        } else {
            temp = len;
        }
    }

    return value;
}
