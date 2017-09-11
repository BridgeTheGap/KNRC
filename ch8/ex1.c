#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void error(char *fmt, ...);

/* cat:  concatenate files, v2 */
int main(int argc, char *argv[]) {
    int fd;
    void filecopy(int, int);
    char *prog = argv[0];

    if (argc == 1) {
        filecopy(0, 1);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) < 0) {
                error("%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fd, 1);
                close(fd);
            }
        }
    }
    if (ferror(stdout)) {
        error("%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}

/* filecopy:  copy file ifd to file ofd */
void filecopy(int ifd, int ofd) {
    char c;
    while (read(ifd, &c, 1) == 1) {
        if (write(ofd, &c, 1) != 1) {
            error("filecopy: can't write %c", c);
        }
    }
}
