#include <stdio.h>
#include <string.h>

#define MAXLINES 5000     /* max #lines to be sorted */
char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(void *lineptr[], int left, int right, 
            int(*comp)(void *, void *));
void rqsort(void *lineptr[], int left, int right, 
            int(*comp)(void *, void *));
int _strcmp(char *s, char *t);
int cistrcmp(char *s, char *t);
int numcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines;       /* number of input lines read */
    int numeric = 0;  /* 1 if numeric sort */
    int reverse = 0, ci = 0;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (_strcmp(argv[i], "-n") == 0) {
                numeric = 1;
            }    
            if (_strcmp(argv[i], "-r") == 0) {
                reverse = 1;
            }
            if (_strcmp(argv[i], "-f") == 0) {
                ci = 1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (reverse) {
            rqsort((void **)lineptr, 0, nlines-1,
                   (int (*)(void *, void *))(numeric ? numcmp : 
                                             ci ? cistrcmp : _strcmp));
            writelines(lineptr, nlines);
        } else {
            _qsort((void **) lineptr, 0, nlines-1,
                   (int (*)(void*,void*))(numeric ? numcmp : 
                                          ci ? cistrcmp : _strcmp));
            writelines(lineptr, nlines);
        }
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* _qsort:  sort v[left]...v[right] into increasing order */
void _qsort(void *v[], int left, int right,
           int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) { 
        return ; 
    }
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    _qsort(v, left, last-1, comp);
    _qsort(v, last+1, right, comp);
}

void rqsort(void *v[], int left, int right,
            int (*comp)(void *, void *)) {
    int i, last;
        void swap(void *v[], int, int);

    if (left >= right) { 
        return ; 
    }
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) > 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    rqsort(v, left, last-1, comp);
    rqsort(v, last+1, right, comp);
}

int cistrcmp(char *s, char *t) {
    while (*s != '\0') {
        if (*s != *t) {
            if ((*s >= 'a' && *s <= 'z') && 
                (*t >= 'A' && *t <= 'Z')) 
            {
                if ((*s - 32) != *t) {
                    return (*s-32) - *t;
                }
            } else if ((*s >= 'A' && *s <= 'Z') &&
                       (*t >= 'a' && *t <= 'z'))
            {
                if ((*s + 32) != *t) {
                    return (*s+32) - *t;
                }
            } else {
                return *s - *t;
            }
        }
        s++;
        t++;
    }
    return 0;
}

#include <stdlib.h>

/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
