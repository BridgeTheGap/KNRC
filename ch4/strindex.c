#include <time.h>
#include <stdio.h>
#define MAXLINE 1000    /* maximum input line length */

int _getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";    /* pattern to search for */

/* find all lines matching pattern */
int main() {
    char line[MAXLINE];
    int found = 0;

    // clock_t tic = clock();

    // for (int i = 0; i < 14400000; i++) {
    //     if (strindex("iiiii iiiii iiiii ould iiiii iiiii iiiii", pattern) < 0) {
    //         printf("error\n");
    //     }
    // }

    while (_getline(line, MAXLINE) > 0 ) {
        if (strindex(line, pattern) >= 0) {
            printf("%s\n", line);
            found++;
        }
    }

    // clock_t toc = clock();

    // printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return found;
}

/* strindex:  return index of t in s, -1 if none */
int strindex(char s[], char t[]) {
    int i, j, k;
    
    for (i = 0; s[i] != '\0'; i++) {
        for (j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++) {}
        if (k > 0 && t[k] == '\0') {
            return i;
        }
    }
    return -1;
}

       
