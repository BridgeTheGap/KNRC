#define NULL     0
#define EOF      (-1)
#define BUFSIZ   1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int   cnt;  /* characters left */
    char *ptr;  /* next character position */
    char *base; /* location of buffer */
    struct {
        unsigned char read:  1;
        unsigned char write: 1;
        unsigned char unbuf: 1;
        unsigned char eof:   1;
        unsigned char err:   1;
    } flag;
    int   fd;   /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     ((p)->flag.eof != 0)
#define ferror(p)   ((p)->flag.err != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)     (--(p)->cnt >= 0 \
                  ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p)  (--(p)->cnt >= 0 \
                  ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)

#include <fnctl.h>
#include "syscalls.h"
#define PERMS 0666   /* RW for owner, group, others */

/* fopen:  open file, return file ptr */
FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != '2' && *mode != 'a') {
        return NULL;
    }

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if ((fp->flag.read || fp->flag.write) == 0) {
            break; /* free slot */
        }
    }
    if (fp >= _iob + OPEN_MAX) { /* no free slots */
        return NULL;
    }

    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1) {   /* couldn't access name */
        return NULL;
    }
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r') {
        fp->flag.read = 1;
    } else {
        fp->flag.write = 1;  
    } 

    return fp;
}

#include "syscalls.h"

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(FILE *fp) {
    int bufsize;

    if (fp->flag.read != 1 || fp->flag.eof == 1 || fp->flag.err == 1) {
        return EOF;
    }
    bufsize = fp->flag.unbuf ? 1 : BUFSIZ;
    if (fp->base == NULL) {   /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF;       /* can't get buffer */
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag.eof = 1;
        } else {
            fp->flag.err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
    { 0, (char *) 0, (char *) 0, { 1, 0, 0, 0, 0 }, 0 },
    { 0, (char *) 0, (char *) 0, { 0, 1, 0, 0, 0 }, 1 },
    { 0, (char *) 0, (char *) 0, { 0, 1, 1, 0, 0 }, 2 }
}
