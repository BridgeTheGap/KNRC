#include <stdio.h>

int main() {

    /* Celsius to Fahrenheit */
    int start, end;
    float c, f, step;

    start = 0;
    end = 100;

    c = (float)start;
    step = 10.0;

    printf("Celsius    Fahrenheit\n");

    while (c <= end) {
        f = c * 9.0/5.0 + 32.0;
        printf("%7.0f    %.1f\n", c, f);
        c += step;
    }

}