#include <stdio.h>

typedef struct _file_v1 {
    int flag;
} File_v1;

enum _flags {
    _READ  = 01,  /* file open for reading */
    _WRITE = 02,  /* file open for writing */
    _UNBUF = 04,  /* file is unbuffered */
    _EOF   = 010, /* EOF has occurred on this file */
    _ERR   = 020  /* error occurred on this file */
};

typedef struct _file_v2 {
    struct {
        unsigned char read:  1;
        unsigned char write: 1; 
        unsigned char unbuf: 1;
        unsigned char eof:   1;
        unsigned char err:   1;
    } flag;
} File_v2;

int main() {
    File_v1 fp0arr[] = {
        { _READ },
        { _WRITE },
        { _WRITE|_UNBUF },
        { 0 },
    };
    
    File_v2 fp1arr[] = {
        { { 1, 0, 0, 0, 0 } },
        { { 0, 1, 0, 0, 0 } },
        { { 0, 1, 1, 0, 0 } },
        { { 0, 0, 0, 0, 0 } },
    };
    
    for (int i = 0; i < 4; i++) {
        File_v1 *fp0 = fp0arr + i;
        File_v2 *fp1 = fp1arr + i;

        printf("Struct %d\n", i);

        int r1 = (fp0->flag & (_READ|_WRITE)) == 0;
        int r2 = (fp1->flag.read || fp1->flag.write) == 0;

        printf("= Test 1: %s\n", r1 == r2 ? "PASS" : "FAIL");
        
        int f = fp0->flag;
        fp0->flag = (i % 2) ? _READ : _WRITE;

        int r = fp1->flag.read;
        int w = fp1->flag.write;

        if (i % 2) { 
            fp1->flag.read = 1; 
            fp1->flag.write = 0; 
        } else { 
            fp1->flag.read = 0; 
            fp1->flag.write = 1;
        }
        
        int r3 = fp0->flag;
        fp0->flag = f;

        int r4;        
        if (i % 2) {
            r4 = fp1->flag.read == 1 ? _READ : 0;
        } else {
            r4 = fp1->flag.write == 1 ? _WRITE : 0;
        }
        fp1->flag.read = r;
        fp1->flag.write = w;

        printf("= Test 2: %s\n", r3 == r4 ? "PASS" : "FAIL");
        
        int r5 = (fp0->flag&(_READ|_EOF|_ERR)) != _READ;
        int r6 = fp1->flag.read != 1 || fp1->flag.eof == 1 || fp1->flag.err == 1;
        printf("= Test 3: ");
        if (r5 == r6) {
            printf("PASS\n");
        } else {
            printf("FAIL (r5: %d, r6: %d)\n", r5, r6);
        }

        printf("= Test 4: ");
        int r7 = fp0->flag & _UNBUF ? 1 : 1024;
        int r8 = fp1->flag.unbuf ? 1 : 1024;
        if (r7 == r8) {
            printf("PASS\n");
        } else {
            printf("FAIL (r7: %d, r8: %d)\n", r7, r8);
        }

        printf("= Test 5: ");
        fp0->flag |= i%2 ? _EOF : _ERR;
        if (i%2) {
            fp1->flag.eof = 1;
        } else {
            fp1->flag.err = 1;
        }

        int r9 = i%2 ? (fp0->flag & _EOF) != 0 : (fp0->flag & _ERR) != 0;
        int r10 = i%2 ? fp1->flag.eof == 1 : fp1->flag.err == 1;
        
        if (r9 == r10) {
            printf("PASS\n");
        } else {
            printf("FAIL (r9: %d, r10: %d)\n", r9, r10);
        }

        printf("\n");
    }

    return 0;
}