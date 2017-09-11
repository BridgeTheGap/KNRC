#include <stdlib.h>
#include <stdio.h>

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header  base;           /* empty list to get started */
static Header *freep = NULL;  /* start of free list */
static Header *morecore(unsigned);

#define MAXALLOC (1024 * sizeof(int))

/* _malloc:  general-purpose storage allocator */
void *_malloc(unsigned nbytes) {
    if (nbytes > MAXALLOC) {
        fprintf(stderr, "error: exceeded max memory allocation limit of %lu\n", 
                MAXALLOC);
        exit(1);
    }

    Header *p, *prevp;
    unsigned nunits; 

    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {  /* big enough */
            if (p->s.size == nunits) {
                prevp->s.ptr = p->s.ptr;
            } else {                /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep) { /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL) {
                return NULL; /* none left */
            }
        }
    }
}

#define NALLOC 1024  /* minimum #units to request */

/* morecore:  ask system for more memory */
Header *morecore(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC) {
        nu = NALLOC;
    }
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) {  /* no space at all */
        return NULL;
    }
    up = (Header *)cp;
    up->s.size = nu;
    free((void *)(up+1));
    return freep;
}

/* free:  put block ap in free list */
void free(void *ap) {
    if (sizeof ap > MAXALLOC) {
        fprintf(stderr, "error: exceeded max memory allocation limit of %lu\n",
                MAXALLOC);
        exit(1);
    }

    Header *bp, *p;

    bp = (Header *)ap - 1;    /* point to block header */

    //: Continue loop iteration until if bp is between current free pointer
    //  and the next, or if free pointer has reached the end and the next
    //  free position is beyond the current free block

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break;  /* freed block at start or end of arena */
        }
    }

    if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp) {         /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}

#define ARRSIZ 1024

int main() {
    int *arr = _malloc(ARRSIZ * sizeof(int));
    for (int i = 0; i < ARRSIZ; i++) {
        printf("%d ", *(arr+i));
        if ((i+1) % 40 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    return 0;
}