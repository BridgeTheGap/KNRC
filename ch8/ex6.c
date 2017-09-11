#include <stdlib.h>
/* _calloc:  returns a pointer to n objects of size `size`, 
            initialized to zero  */
void *_calloc(int n, int size) {
    void *p;
    p = malloc(n * size);
    for (int i = 0; i < n * size; i++) {
        *((char *)p+i) = 0;
    }
    return p;
}

#include <stdio.h>

#define ARRSIZ 20

int main() {
    printf("calloc\n");
    int *array = _calloc(ARRSIZ, sizeof(int));
    for (int i = 0; i < ARRSIZ; i++) {
        if (array[i] != 0) {
            printf("[%d] %d; ", i, array[i]);
        }
    }
    printf("\n");

    printf("malloc\n");
    int *array2 =  malloc(sizeof(int) * ARRSIZ);
    for (int i = 0; i < ARRSIZ; i++) {
        if (array2[i] != 0) {
            printf("[%d] %d; ", i, array2[i]);    
        }
    }
    printf("\n");

    return 0;
}