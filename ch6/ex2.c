struct node {
    char *word;
    struct node *left;
    struct node *right;
    struct node *root;
};

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct node *addtree(struct node *, char *, int);
void treeprint(struct node *);
int getword(char *, int);

static int n;

int main(int argc, char *argv[]) {
    if (argc == 2) {
        n = atoi(argv[1]);
        struct node *mroot = NULL;
        char word[MAXWORD];
        
        while (getword(word, MAXWORD) != EOF) {
        // 1. Compare the first n characters
        // 2. If matching, add to subtree
        // 3. If not a match, add node to main tree
            mroot = addtree(mroot, word, 0);
        }

        printf("Binary tree of words matching %d characters...\n", n);
        treeprint(mroot);
    } else {
        printf("ex2 [n]\n"
               "- n: number of characters to match.\n");
    }

    return 0;
}

struct node *talloc(void);
char *_strdup(char *);
char *_strndup(char *, int);

/* addtree:  add a node with w, at or below p */
struct node *addtree(struct node *p, char *w, int subtree) {
    int cond;

    if (subtree) {
        if (p == NULL) {
            p = talloc();
            p->word = _strdup(w);
            p->left = p->right = p->root = NULL;
        } else if ((cond = strcmp(w, p->word)) < 0) {
            p->left = addtree(p->left, w, 1);
        } else if (cond > 0) {
            p->right = addtree(p->right, w, 1);
        }
    } else {
        if (p == NULL) {
            p = talloc();
            p->word = _strndup(w, n);
            p->left = p->right = p->root = NULL;
            p->root = addtree(p->root, w, 1);
        } else if ((cond = strncmp(w, p->word, n)) == 0) {
            p->root = addtree(p->root, w, 1);
        } else if (cond < 0) {
            p->left = addtree(p->left, w, 0);
        } else {
            p->right = addtree(p->right, w, 0);
        }
    }
    return p;
}

/* treeprint:  in-order print of tree p */
void treeprint(struct node *p) {
    if (p != NULL) {
        treeprint(p->left);

        if (p->root != NULL) {
            printf("List for %s\n", p->word);
            treeprint(p->root);
        } else {
            printf("- %s\n", p->word);
        }
        
        treeprint(p->right);
    }
}

/* talloc:  make a node */
struct node *talloc(void) {
    return (struct node *) malloc(sizeof(struct node));
}

/* _strdup:  make a duplicate of s */
char *_strdup(char *s) {
    char *p;

    p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

/* _strndup:  make a duplicate of s of length n */
char *_strndup(char *s, int n) {
    char *p;

    p = (char *) malloc(n + 1);
    if (p != NULL) {
        strncpy(p, s, n);
    }
    return p;
}
