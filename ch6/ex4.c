struct wnode {
    char *word;
    int count;
    struct wnode *left;
    struct wnode *right;
};

#include <stdio.h>
#include <string.h>

#define MAXWORD 100

char *_strdup(char *);
struct wnode *walloc(void);
struct wnode *addtree(struct wnode *, char *);
struct wnode *addotree(struct wnode *, struct wnode *);

struct wnode *pop(struct wnode *);

void printtree(struct wnode *);

int getword(char *, int);

static int line = 1;

int main() {
    char w[MAXWORD];
    int ignore;
    struct wnode *root = NULL;

    while (getword(w, MAXWORD) != EOF) {
        root = addtree(root, w);
    }

    printf("Alphabetical order..\n");
    printtree(root);

    struct wnode *nroot = NULL;
    struct wnode *p;

    while ((p = pop(root))) {
        nroot = addotree(nroot, p);
        if (p == root) {
            break;
        }
    }

    printf("Occurence order..\n");
    printtree(nroot);

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

struct wnode *addtree(struct wnode *p, char *word) {
    int result;
    if (p == NULL) {
        p = walloc();
        p->word = _strdup(word);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((result = strcmp(word, p->word)) == 0) {
        p->count++;
    } else if (result < 0) {
        p->left = addtree(p->left, word);
    } else {
        p->right = addtree(p->right, word);
    }
    return p;
}

struct wnode *pop(struct wnode *root) {
    if (root->left != NULL) {
        struct wnode *node = pop(root->left);
        if (node == root->left) {
            root->left = NULL;    
        }
        return node;
    } else if (root->right != NULL) {
        struct wnode *node = pop(root->right);
        if (node == root->right) {
            root->right = NULL;    
        }
        return node;
    } else {
        return root;
    }
}

struct wnode *addotree(struct wnode *root, struct wnode *p) {
    if (root == NULL) { 
        return p;
    }

    int cond = p->count > root->count ? -1 :
               p->count < root->count ? 1 : 
               strcmp(p->word, root->word);

    if (cond < 0) {
        if (root->left == NULL) {
            root->left = p;
        } else {
            root->left = addotree(root->left, p);
        }
    } else if (cond > 0) {
        if (root->right == NULL) {
            root->right = p;
        } else {
            root->right = addotree(root->right, p);
        }
    }

    return root;
}

void printtree(struct wnode *root) {
    if (root != NULL) {
        printtree(root->left);
        printf("%4d %s\n", root->count, root->word);
        printtree(root->right);
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