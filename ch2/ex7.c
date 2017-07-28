#include <stdio.h>

unsigned int invert(unsigned int x, 
                    unsigned int p, 
                    unsigned int n);

int main() {
    unsigned int x = 3276;
    unsigned int p = 8;
    unsigned int n = 4;

    printf("x = %u, p = %u, n = %u\n", x, p, n);
    printf("result = %u\n", invert(x, p, n));

    return 0;
}

unsigned int invert(unsigned int x, 
                    unsigned int p, 
                    unsigned int n) 
{    
    unsigned int a = ~(~0 << n) << (p+1-n);
    return x ^ a;
}