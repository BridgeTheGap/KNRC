#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main() {
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES, char [1000])) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line */
int _getline(char *, int);
void _strcpy(char *, char *);
char *alloc(int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines, char p[]) {
    int len, nlines;
    char *line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines) {
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
