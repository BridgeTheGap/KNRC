#include <time.h>
#include <stdio.h>

int bitcount(unsigned);

int main() {
    clock_t tic = clock();

    for (int i = 0; i < 1444000; i++) {
        if (bitcount(60278) != 11) {
            printf("FAILURE\n");
        }
    }

    clock_t toc = clock();

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}

int bitcount(unsigned x) {
    int b;

    for (b = 0; x != 0; x &= (x-1)) {
        ++b;
    }

    return b;

    // int b;
    // for (b = 0; x != 0; x >>= 1) {
    //     if (x & 01) { b++; }
    // }
    // return b;
}

