#include <stdio.h>

#define MAX 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main() {
    int c, i;
    char s[MAX], t[MAX];
    i = 0;

    while ((c = getchar()) != EOF) {
        t[i++] = c;
    }
    t[i] = '\0';

    escape(s, t);
    printf("Escaped:\n%s\n", s);
    unescape(t, s);
    printf("Unescaped:\n%s\n", t);

    return 0;
}

void escape(char s[], char t[]) {
    int i, j;
    i = j = 0;

    while (t[j++] != '\0') {
        switch (t[j-1]) {
            case '\a':
                s[i++] = '\\';
                s[i++] = 'a';
                break;
            case '\b':
                s[i++] = '\\';
                s[i++] = 'b';
                break;
            case '\f':
                s[i++] = '\\';
                s[i++] = 'f';
                break;
            case '\n':
                s[i++] = '\\';
                s[i++] = 'n';
                break;
            case '\r':
                s[i++] = '\\';
                s[i++] = 'r';
                break;
            case '\t':
                s[i++] = '\\';
                s[i++] = 't';
                break;
            case '\v':
                s[i++] = '\\';
                s[i++] = 'v';
                break;
            case '\\':
                s[i++] = '\\';
                s[i++] = '\\';
                break;
            case '\'':
                s[i++] = '\\';
                s[i++] = '\'';
                break;
            case '\"':
                s[i++] = '\\';
                s[i++] = '"';
                break;
            default:
                s[i++] = t[j-1];
                break;
        }
    }
}

void unescape(char s[], char t[]) {
    int c, e, i, j;
    i = j = e = 0;

    while ((c = t[j++]) != '\0') {
        if (e) {
            switch (c) {
                case 'a':
                    s[i++] = '\a';
                    break;
                case 'b':
                    s[i++] = '\b';
                    break;
                case 'f':
                    s[i++] = '\f';
                    break;
                case 'n':
                    s[i++] = '\n';
                    break;
                case 'r':
                    s[i++] = '\r';
                    break;
                case 't':
                    s[i++] = '\t';
                    break;
                case 'v':
                    s[i++] = '\v';
                    break;
                case '\\':
                    s[i++] = '\\';
                    break;
                case '\'':
                    s[i++] = '\'';
                    break;
                case '"':
                    s[i++] = '"';
                    break;
                default:
                    s[i++] = c;
                    break;
            }
            e = 0;
        } else {
            switch (c) {
                case '\\':
                    e = 1;
                    break;
                default:
                    s[i++] = c;
            }
        }
    }
}