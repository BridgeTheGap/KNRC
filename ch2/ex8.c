#include <time.h>
#include <stdio.h>

unsigned int rightrot(unsigned int x, unsigned int n);

int main() {
    int x, n;
    x = 61635;
    n = 7;
    printf("x = %u, n = %u\n", x, n);
    printf("result = %u\n", rightrot(x, n));

    return 0;
}

unsigned int rightrot(unsigned int x, unsigned int n) {
    unsigned int a, p, temp;
    temp = x;

    for (p = 0; temp > 0; p++) {
        if (p == n) {
            a = x % (temp << n);
        }

        temp = temp >> 1;
    }

    return (a << (p-n)) | (x >> n);

    // while (n > 0) {
    //     if ((x & 1) == 1)
    //         x = (x >> 1) | ~(~0U >> 1);
    //     else
    //         x = (x >> 1);
    //     n--;
    // }
    // return x;
}