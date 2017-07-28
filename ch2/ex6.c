#include <stdio.h>

unsigned int setbits(unsigned int, int, int, int);

int main() {
    int x, p, n, y;
    x = 35305;
    p = 7;
    n = 4;
    y = 13;
    printf("x = %d, p = %d, n = %d, y = %d\n", x, p, n, y);
    printf("result: %d\n", setbits(x, p, n, y));

    return 0;
}

unsigned int setbits(unsigned int x, int p, int n, int y) {
    // 1. Convert all remaining bits of y to 1
    // 2. a | y, whose bits left to position y are all 1
    unsigned int temp, a;
    // printf("%u | %u = %u\n", y, ~0 << n, y|(~0 << n));
    a = (y|(~0 << n)) & ~(~0 << n);
    
    // 3. temp = bits of x right of p-n
    // 4. Set bits of x right of p to 0.
    // 5. x | (a << p-n)
    // 6. x | temp
    temp = (x|(~0 << (p-n+1))) & ~(~0 << (p-n+1));
    x = (x >> (p+1)) << (p+1);
    x = x | (a << (p-n+1));
    return x | temp;
}