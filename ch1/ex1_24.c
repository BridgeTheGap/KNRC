#include <stdio.h>

#define IN  1
#define OUT 0

void check(void);

int main() {
    check();

    return 0;
}

void check(void) {
    int bracket, brace, c, ch, comment, err, line, str, paren, prev;
    bracket = brace = comment = ch = err = line = prev = str = paren = 0;

    while ((c = getchar()) != EOF) {
        if (prev == '\n' || prev == 0) {
            ++line;
            printf("%3d| ", line);
        }

        putchar(c);

        if (c == '\'' && str == OUT && comment == OUT) {
            if (ch == OUT) {
                ch = IN;
            } else if (ch > IN) {
                ch = IN;
            } else {
                ch = OUT;
            }
        } else if (c == '"' && ch == OUT && comment == OUT) {
            if (str == OUT) {
                str = IN;
            } else {
                str = OUT;
            }
        } else if (c == '*' && prev == '/' && ch == OUT && str == OUT) {
            if (comment == OUT) {
                comment = IN + 1;
            }
        } else if (c == '/' && prev == '*' && ch == OUT && str == OUT) {
            if (comment == IN) {
                comment = OUT;
            }
        } else if ((c == '(' || c == ')') && ch == OUT && str == OUT && comment == OUT) {
            if (c == '(') {
                ++paren;
            } else {
                --paren;

                if (paren < OUT) {
                    printf("SYNTAX ERROR: A closing parenthesis without an opening one.\n");
                }
            }
        } else if ((c == '{' || c == '}') && ch == OUT && str == OUT && comment == OUT) {
            if (c == '{') {
                ++brace;
            } else {
                --brace;

                if (brace < OUT) {
                    printf("SYNTAX ERROR: A closing brace without an opening one.\n");
                }
            }
        } else if ((c == '[' || c == ']') && ch == OUT && str == OUT && comment == OUT) {
            if (c == '[') {
                ++bracket;
            } else {
                --bracket;

                if (bracket < OUT) {
                    printf("SYNTAX ERROR: A closing bracket without an opening one.\n");
                }
            }
        } else {
            if (ch >= IN) { 
                if (prev == '\'') {
                    if (c == '\\') {
                        ++ch;
                    } else if (ch > IN) {
                        printf("SYNTAX ERROR: Invalid character %c.\n", c); 
                        ++err;
                    }
                } else if (prev == '\\') {
                    if (ch > IN) {
                        ch = IN;
                    } else {
                        printf("SYNTAX ERROR: Invalid character %c.\n", c); 
                        ++err;
                    }
                }

            } else if (comment > OUT) {
                if (comment == IN + 1) {
                    comment = IN;
                }
            } 
        }

        prev = c;
    }

    printf("\n================ FINISHED SYNTAX ERROR CHECK ==============\n");

    if (bracket != OUT || 
        brace != OUT || 
        ch != OUT ||
        comment != OUT || 
        str != OUT || 
        paren != OUT) 
    {
        printf("SYNTAX ERROR: A bracket, brace, character, comment, string, or parenthesis hansn't been closed.\n");
        ++err;
    }

    printf("%d errors found in file.\n", err);
}

/* 
  1. Don't change state for chars in '' or strings in ""
     ex) '"', "'", "\"\"", '{', "{}", etc.
  2. If in comment, ignore "". If in string, ignore comment sequences.
*/