#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int _getline(char *line, int max);

/* find:  print lines that match pattern from 1st arg */
int main(int argc, char *argv[]) {
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
        }
    }

    if (argc > 0) {
        char *pattern = *argv++;
        FILE *f;

        while ((f = argc == 1 ? stdin : fopen(*argv++, "r")) != NULL &&
               fgets(line, MAXLINE, f) != NULL)
        {
            lineno++;
            if ((strstr(line, pattern) != NULL) != except) {
                if (number) {
                    printf("%ld:", lineno);
                }
                printf("%s", line);
                found++;
            }
        }

    } else {
        printf("Usage: find -x -n pattern filename...\n");
    }

    return found;
}
