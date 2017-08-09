#include <stdio.h>

#define swap(t,x,y) { t temp = x; x = y; y = temp; }

int main() {
    double x, y;
    x = 1.5;
    y = 2.5;
    printf("x = %g; y = %g\n", x, y);
    swap(double, x, y);
    printf("x = %g; y = %g\n", x, y);
    return 0;
}