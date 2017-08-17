#include <stdio.h>

#define MAXLEN 1000 /* max length of any input line */
int _getline(char *, int);
void _strcpy(char *, char *);
char *alloc(int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0'; /* delete newline */
            _strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

/* writelines v2:  pointer version */
/*
void writelines(char *lineptr[], int nlines) {
    while (nlines-- < 0) {
        printf("%s\n", *lineptr++);
    }
}
*/
