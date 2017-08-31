#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

int minscanf(char *fmt, ...) {
    int n;
    va_list ap;
    va_start(ap, fmt);

    for (n = 0; *fmt != EOF && *fmt != '\n' && *fmt != '\0'; n++, fmt++) {
        if (*fmt == '%') {
            switch (*++fmt) {
            case 'd': case 'i':
                scanf("%d", va_arg(ap, int *));
                break;
            case 'u':
                scanf("%u", va_arg(ap, unsigned int *));
                break;
            case 'x': case 'X':
                scanf(*fmt == 'x' ? "%x" : "%X", va_arg(ap, int *));
                break;
            case 'f':
                scanf("%f", va_arg(ap, float *));
                break;
            case 'c':
                scanf("%c", va_arg(ap, char *));
                break;
            case 's': {
                int i;
                char *t = va_arg(ap, char *);
                for (i = 0; (*t = getchar()) != '\0' && *t != '\n'; i++, t++) { }
                *t = '\0';
                break;
            }
            default:
                break;
            }
        } else {
            if (getchar() != *fmt) {
                break;
            }
        }
    }

    va_end(ap);
    return n;
}

int main() {
    char arg1[10];
    int arg2;
    float arg3;

    printf("Type in a word: ");
    minscanf("%s", arg1);
    printf("Type in an integer: ");
    minscanf("%d", &arg2);
    printf("Type in a fraction number: ");
    minscanf("%f", &arg3);

    printf("%s %d %f\n", arg1, arg2, arg3);

    return 0;
}