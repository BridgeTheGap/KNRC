#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2 || strlen(argv[1]) != 4) { 
        printf("Usage: ./bf [a][b][c][d]\n"
               "       -[a/b/c/d]: 0 or 1\n"); 
        exit(1);
    }


    int arr[4];

    for (int i = 0; i < 4; i++) {
        arr[i] = *argv[1]++;
    }

    struct {
        unsigned char one: 1;
        unsigned char two: 1;
        unsigned char three: 1;
        unsigned char four: 1;
    } flag = { arr[0], arr[1], arr[2], arr[3] };

    if (flag.one) {
        printf("one is set\n");
    }
    if (flag.two) {
        printf("two is set\n");
    }
    if (flag.three) {
        printf("three is set\n");
    }
    if (flag.four) {
        printf("four is set\n");
    }

    return 0;
}