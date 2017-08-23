#include <stdio.h>
#include <ctype.h>

/* getword:  get next word or character from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch())) { }

    if (c == '"') {
        while ((c = getch()) != '"' && c != '\n') { }
        c = getch();
    }
    if (c == '/') {
        if ((c = getch()) == '*') {

            while ((c = getch()) != '*'
                && (c = getch()) != '/') { 
                ungetch(c);
            }
            c = getch();
        } else {
            ungetch(c);
            c = '/';
        }
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }       
    }
    *w = '\0';
    return word[0];
}
