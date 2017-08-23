struct nnode {
    int line;
    struct nnode *next;
};

struct wnode {
    char *word;

    struct nnode *list;
    struct wnode *left;
    struct wnode *right;
};

#define IGNORE(w) (strcmp("the", w) == 0 ||\
                   strcmp("a", w) == 0 ||\
                   strcmp("an", w) == 0)

#include <stdio.h>
#include <string.h>

#define MAXWORD 100

char *_strdup(char *);

struct wnode *walloc(void);
struct nnode *nalloc(void);

struct wnode *addtree(struct wnode *, char *);
struct nnode *addlist(struct nnode *);

void printtree(struct wnode *);
void printlist(struct nnode *);

int getword(char *, int);

static int line = 1;

int main() {
    char w[MAXWORD];
    int ignore;
    struct wnode *root = NULL;

    while (getword(w, MAXWORD) != EOF) {
        if (!IGNORE(w)) {
            root = addtree(root, w);
        }
    }

    printf("\nIndexing words...\n");
    printtree(root);

    return 0;
}

#include <stdlib.h>

char *_strdup(char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

struct wnode *walloc(void) {
    return (struct wnode *) malloc(sizeof(struct wnode));
}

struct nnode *nalloc(void) {
    return (struct nnode *) malloc(sizeof(struct nnode));
}

struct wnode *addtree(struct wnode *p, char *word) {
    int result;
    if (p == NULL) {
        p = walloc();
        p->word = _strdup(word);
        p->list = NULL;
        p->left = p->right = NULL;
        p->list = addlist(p->list);
    } else if ((result = strcmp(word, p->word)) == 0) {
        addlist(p->list);
    } else if (result < 0) {
        p->left = addtree(p->left, word);
    } else {
        p->right = addtree(p->right, word);
    }
    return p;
}

struct nnode *addlist(struct nnode *p) {
    if (p == NULL) {
        p = nalloc();
        p->line = line;
        p->next = NULL;
    } else if (p->line < line) {
        p->next = addlist(p->next);
    }
    return p;
}

void printtree(struct wnode *root) {
    if (root != NULL) {
        printtree(root->left);
        printf("- %-10s: ", root->word);
        printlist(root->list);
        printtree(root->right);
    }
}

void printlist(struct nnode *s) {
    if (s != NULL) {
        printf("%d", s->line);
        if (s->next == NULL) {
            printf("\n");
        } else {
            printf(", ");
            printlist(s->next);
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
    while ((isspace(c = getch()) || !isalpha(c)) && i++ < lim) { 
        if (c == '\n') {
            line++;
        }
    }

    if (c == EOF) {
        return EOF;
    } else {
        *w++ = c;
    }

    while ((isalpha(c = getch()) || c == '\'') && i++ < lim) { 
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