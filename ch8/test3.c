#include <stdio.h>
#include <string.h>

typedef struct _SomeStruct {
    int   cnt;
    char *ptr;
} SomeStruct;

#define putc(x, p)  (--(p)->cnt >= 0 \
                  ? *(p)->ptr++ = (x) : -10)

int main() {
    char str[] = "hello, world";
    SomeStruct s1 = { strlen(str), str };
    SomeStruct *p = &s1;

    printf("%d %s; %s\n", p->cnt, p->ptr, str);
    printf("%d\n", putc('c', p));
    printf("%d %s; %s\n", p->cnt, p->ptr, str);

    return 0;
}