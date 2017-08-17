#include <stdio.h>

int main(int argc, char *argv[]) {
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }
    int (*ptr)[] = &array;
    printf("%d\n", *((*ptr)+3));

    return 0;
}
