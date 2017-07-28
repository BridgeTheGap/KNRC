#include <stdio.h>

#define LOWER 0       /* lower limit of table */
#define UPPER 300     /* upper limit */
#define STEP  20      /* step size */

/* print Fahrenheit-Celsius table */

float fahrenheitToCelsius(float f);

int main()
{
    int fahr;

    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP) {
        printf("%3d %6.1f\n", fahr, fahrenheitToCelsius(fahr));
    }
}

float fahrenheitToCelsius(float f) {
    return (5.0/9.0)*(f-32);
}