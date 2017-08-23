#include <stdio.h>
#include <string.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void printtable(void);

int getword(char *, int);

int main() {
    char w[100];
    char *name = NULL;
    
    while ((getword(w, 100)) != EOF) {
        if (name == NULL) {
            name = strdup(w);
        } else {
            install(name, strdup(w));
            name = NULL;
        }
    }

    printtable();

    return 0;
}

#include <stdlib.h>

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash:  form has value for string */
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}

/* install:  put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->defn);
    }

    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

void printtable(void) {
    for (int i = 0; i < HASHSIZE; i++) {
        struct nlist *p;
        if ((p = hashtab[i]) != NULL) {
            printf("[hash: %d]\n", i);
            do {
                printf("name: %s; def: %s\n", p->name, p->defn);
            } while ((p = p->next) != NULL);
        }
    }
}

#include <ctype.h>

static int buf;

/* getword:  get next word or character from input */
int getword(char *word, int lim) {
    int c, i, getch(void);
    char *w = word;

    i = 0;
    while ((isspace(c = getch()) || !isalnum(c)) && i++ < lim) { }

    if (c == EOF) {
        return EOF;
    } else {
        *w++ = c;
    }

    while ((isalnum(c = getch()) || c == '\'') && i++ < lim) { 
        *w++ = c;
    }
    buf = c;
    *w = '\0';
    
    return word[0];
}

int getch(void) {
    if (buf == 0) {
        return getchar();
    } else {
        int copy = buf;
        buf = 0;
        return copy;
    }
}