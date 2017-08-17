#include <stdio.h>
#include <string.h>

#define MAXLINES 5000     /* max #lines to be sorted */
char *lineptr[MAXLINES];  /* pointers to text lines */
int option;

enum cmp_option {
    none,
    case_insensitive = 1,
    alphanumeric     = 1 << 1,
};

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(void *lineptr[], int left, int right, 
            int(*comp)(void *, void *));
void rqsort(void *lineptr[], int left, int right, 
            int(*comp)(void *, void *));
int _strcmp(char *s, char *t);
int numcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines;       /* number of input lines read */
    int numeric = 0;  /* 1 if numeric sort */
    int reverse = 0;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strchr(argv[i], '-') == argv[i]) {
                if (strchr(argv[i], 'n') != NULL) {
                    numeric = 1;
                }    
                if (strchr(argv[i], 'r') != NULL) {
                    reverse = 1;
                }
                if (strchr(argv[i], 'f') != NULL) {
                    option = option|case_insensitive;
                }
                if (strchr(argv[i], 'd') != NULL) {
                    option = option|alphanumeric;
                }
            }
        }
    }

    char str_options[1024];
    if (numeric) {
        strcat(str_options, "numeric, ");
    }
    if (reverse) {
        strcat(str_options, "reverse, ");
    }
    if (option & case_insensitive) {
        strcat(str_options, "case insensitive, ");
    }
    if (option & alphanumeric) {
        strcat(str_options, "alphanumeric and space only");
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (reverse) {
            rqsort((void **)lineptr, 0, nlines-1,
                   (int (*)(void *, void *))(numeric ? numcmp : _strcmp));
            printf("=== Sorted descending...%s\n", str_options);
            writelines(lineptr, nlines);
        } else {
            _qsort((void **) lineptr, 0, nlines-1,
                   (int (*)(void*,void*))(numeric ? numcmp : _strcmp));
            printf("=== Sorted ascending...%s\n", str_options);
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


#include <ctype.h>

int charcmp(char s, char t) {
    if (s != t) {
        return s - t;
    }
    return 0;
}

int cicharcmp(char s, char t) {
    if (s != t) {
        if (islower(s) && isupper(t)) {
            if ((s - 32) != t) {
                return (s-32) - t;
            }
        } else if (isupper(s) && islower(t)) {
            if ((s + 32) != t) {
                return (s+32) - t;
            }
        } else {
            return s - t;
        }
    }
    return 0;
}

int _strcmp(char *s, char *t) {
    int result;
    while (*s != '\0') {
        if (*s != *t) {
            switch (option) {
            
            case alphanumeric: 
            case case_insensitive|alphanumeric: {
                int shouldcmp = 1;
                if (*s != ' ' && !isalnum(*s)) {
                    shouldcmp = 0;
                    s++;
                }
                if (*t != ' ' && !isalnum(*t)) {
                    shouldcmp = 0;
                    t++;
                }
                if (shouldcmp) {
                    if ((result = option|case_insensitive ? cicharcmp(*s, *t) : charcmp(*s, *t)) != 0) {
                        return result;
                    } else {
                        s++;
                        t++;
                    }
                }
                break;
            }

            case case_insensitive:
            default:
                if ((result = option & case_insensitive ? cicharcmp(*s, *t) : charcmp(*s, *t))) {
                    return result;
                }
                s++;
                t++;
                break;
            }
        } else {
            s++;
            t++;
        }
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
