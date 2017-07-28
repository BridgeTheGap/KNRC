#include <stdio.h>

void printCharRange(void);
void printShortRange(void);
void printIntRange(void);
// void printLongRange(void);

void printUCharRange(void);
void printUShortRange(void);
void printUIntRange(void);
// void printULongRange(void);

int main() {
    printCharRange();
    printShortRange();
    printIntRange();
    // printLongRange();

    printUCharRange();
    printUShortRange();
    printUIntRange();
    // printULongRange();
}

void printCharRange(void) {
    char a = 0;
    while (a >= 0) {
        ++a;
    }
    printf("Min value of char: %d\n", a);
    
    --a;
    printf("Max value of char: %d\n", a);    
}

void printShortRange(void) {
    short int a = 0;
    while (a >= 0) {
        ++a;
    }
    printf("Min value of short int: %d\n", a);

    --a;
    printf("Max value of short int: %d\n", a);
}

void printIntRange(void) {
    int a = 0;
    while (a >= 0) {
        ++a;
    }
    printf("Min value of int: %d\n", a);

    --a;
    printf("Max value of int: %d\n", a);
}

// void printLongRange(void) {
//     long int a = 0;
//     while (a >= 0) {
//         ++a;
//     }
//     printf("Min value of long int: %ld\n", a);

//     --a;
//     printf("Max value of long int: %ld\n", a);
// }

void printUCharRange(void) {
    unsigned char a = 1;
    while (a > 0) {
        ++a;
    }
    
    --a;
    printf("Max value of unsigned char: %u\n", a);
}

void printUShortRange(void) {
    unsigned short int a = 1;
    while (a > 0) {
        ++a;
    }
    --a;
    printf("Max value of unsigned short int: %u\n", a);
}

void printUIntRange(void) {
    unsigned int a = 1;
    while (a > 0) {
        ++a;
    }
    --a;
    printf("Max vlaue of unsigned int: %u\n", a);
}

