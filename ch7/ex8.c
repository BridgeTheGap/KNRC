#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE 65
#define LINE 120

void printBorder(char *);
void printFooter(char *, int);

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *fp;
        int line, page;

        while (--argc > 0) {
            // 1. load file. if fails, return 2
            // 2. print file name. print new line.
            // 3. while line < 65, print contents of file. wrap around 80 char.
            // 4. if line == 65, print page end, page #, line = 0. Repeat 3.
            // 5. If end of file, print new lines until line == 65.
            // 6. if next file != NULL, repeat 2.

            if ((fp = fopen(*++argv, "r")) != NULL) {
                int remainder;
                char s[LINE];

                char h[LINE];
                sprintf(h, "[File name: %s] ", *argv);
                printBorder(h);

                line = 3;
                page = 1;
                
                while (fgets(s, LINE, fp) != NULL) {
                    if (line++ < PAGE-2) {
                        printf("%s", s);
                    } else {
                        printf("%s", s);
                        printFooter(h, page++);
                        line = 0;
                    }
                }

                if (line == 0) {
                    continue;
                }            

                while (line++ < PAGE-1) {
                    putchar('\n');
                }

                printFooter(h, page++);
            } else {
                fprintf(stderr, "error: invalid file name %s\n", *argv);
                exit(2);
            }

        }
    } else {
        fprintf(stderr, "Usage: %s [filename...]\n"
                        "- Program requires at least one file name to print.\n", argv[0]);
        exit(1);
    }
    return 0;
}

void printBorder(char *s) {
    printf("%s", s);
    for (int i = 0; i < LINE-strlen(s); i++) {
        putchar('=');
    }
    putchar('\n');
}

void printFooter(char *s, int page) {
    char end[LINE];
    sprintf(end, "== %s (page %d) ", s, page);
    printBorder(end);
}