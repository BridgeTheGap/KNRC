/* fseek:  randomly access file pointer */
int fseek(FILE *fp, long offset, int origin) {
    int bufsize;

    if (fp == NULL) {
        return -1;
    }

    if (lseek(fp->fd, offset, origin) == -1) {
        return -1;
    }

    fp->cnt = 0;
    fp->ptr = NULL;
    if (fp->base != NULL) {
        free(fp->base);
    }
    
    return 0;
}