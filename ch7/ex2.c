#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int c, i, lim;

        lim = atoi(argv[1]);
        i = 0;

        for (i = 0; (c = getchar()) != EOF; i++) {
            if (i == lim) {
                putchar('\n');
                i = 0;
            }

            if ((c >= ' ' && c <= '~') ||
                (c == '\n')) 
            {
                putchar(c);
            } else {
                printf("%x", c);
            }
        }
        
        putchar('\n');
    } else {
        printf("Usage: ex2 -[n]\n"
               "    n: number of characters in a line\n");
    }
    
    return 0;
}
