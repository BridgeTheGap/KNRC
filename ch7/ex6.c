#include <stdio.h>
#include <stdlib.h>

#define MAX 1024

int main(int argc, char *argv[]) {
    if (argc == 3) {
        FILE *lf, *rf;
        if ((lf = fopen(argv[1], "r")) != NULL &&
            (rf = fopen(argv[2], "r")) != NULL) 
        {
            char *ls, *rs;
            ls = malloc(sizeof(char) * MAX + 1);
            rs = malloc(sizeof(char) * MAX + 1);

            while (fgets(ls, MAX, lf) != NULL && 
                   fgets(rs, MAX, rf) != NULL) 
            {
                char *s1 = ls;
                char *s2 = rs;
                while (*s1++ == *s2++ && *s1 != '\0') {  }
                
                if (*s1 != '\0' || *s2 != '\0') {
                    goto diff;
                }
            }

            if (ls != NULL && rs != NULL) {
                printf("No different lines detected.\n");
                free(ls);
                free(rs);
                fclose(lf);
                fclose(rf);

                return 0;
            } else if (ls == NULL) {
                goto diff;
            } else if (rs == NULL) {
                goto diff;
            }

            diff:
            fprintf(stderr, "Difference found..\n"
                            "- L: %s\n"
                            "- R: %s\n", ls, rs);
            free(ls);
            free(rs);
            fclose(lf);
            fclose(rf);
            exit(3);
        } else {
            char *err = "error: failed to open file %s.\n";
            if (lf == NULL) {
                fprintf(stderr, err, argv[1]);
                exit(2);
            }
            if (rf == NULL) {
                fprintf(stderr, err, argv[2]);
                exit(2);
            }
        }
    } else {
        fprintf(stderr, "%s: invalid number of arguments for program.\n"
                        " - required: 3; provided: %d\n", argv[0], argc);
        exit(1);
    }
}