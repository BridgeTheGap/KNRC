/* _flushbuf:  write buffer to file and alloc new buffer */

int _flushbuf(int c, FILE *fp) {
    // 1. if base != NULL, write to file
    //    if return value != requested value, return error
    // 2. read next section
    // 3. return *ptr++ = c
    int bufsize;

    if ((fp->flag & (_WRITE|_EOF|_ERR)) != _WRITE) {
        return EOF;
    }

    if (fp->base == NULL) {
        bufsize = fp->flag & _UNBUF ? 1 : BUFSIZ;
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF;
        }
    } else {
        int size;
        for (size = 0; fp->base+size < fp->ptr; size++) { }
        
        if (write(fp->fd, fp->base, size) != size) {
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->base, bufsize);

    if (--fp->cnt < 0) {
        fp->flag |= cnt == - 1 ? _EOF : _ERR;
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++ = c;
}

void fclose(FILE *fp) {
    if (fp == NULL) {
        return;
    }

    fp->cnt = 0;
    fp->ptr = NULL;
    if (fp->base != NULL) {
        free(fp->base);    
        fp->base = NULL;
    }
    fp->flag = 0;
    close(fp->fd);
}
