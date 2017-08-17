#include <stdio.h>

#define MAX_LEN 1024

int _getline(char s[], int lim);
char *alloc(int);
void _strcpy(char *, char *);
int get_n(char *arg);
void push(char *s, char *queue[], int max);

/* tail:  prints the last n lines of its input */
int main(int argc, char *argv[]) {
    if (argc == 2) {
        int i = get_n(*++argv);
        if (i > 0) {
            char *p, *queue[i];
            char l[MAX_LEN];
            int n, len;
            
            for (n = 0; (len = _getline(l, MAX_LEN)) > 0 && (p = alloc(len)) != NULL; n++) {
                l[len-1] = '\0';  /* delete newline */
                _strcpy(p, l);
                push(p, queue, i);
            }

            int max = i < n ? i : n;
            printf("=== Printing the last %d lines\n", max);

            for (int j = 0; j < max; j++) {
                printf("%s\n", queue[j]);
            }
        } else {
            printf("error: argument `n` must be a number bigger than 0.\n");
        }
    } else {
        printf("Usage: tail -<n>\n");
        printf("    n: The number of lines from end to print; n > 0\n");
    }

    return 0;
}

#include <ctype.h>

int get_n(char *arg) {
    if (*arg++ == '-') {
        int i;
        for (i = 0; isdigit(*arg); arg++) {
            i = i * 10 + (*arg - '0');
        }
        if (i > 0 && (*arg == '\n' || *arg == '\0')) {
            return i;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

void push(char *s, char *queue[], int max) {
    int i;
    for (i = 0; i < max-1; i++) {
        queue[i] = queue[i+1];
    }
    queue[i] = s;
}
