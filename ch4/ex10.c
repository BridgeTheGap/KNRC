#include <stdio.h>
#include <stdlib.h>  /* for atof() */

#define MAXOP  100  /* max size of operand or operator */
#define MAX    1024
#define NUMBER '0'  /* signal that a number was found */

int getop(char s[], char l[]);
void push(double n);
double pop(void);
int _getline(char s[], int lim);
void dequeue(char s[], int i);
void insertnl(char s[]);

void insertnl(char s[]) {
    int i = 0;
    while (s[i++] != '\0') {}
    if (s[i-2] != '\n') {
        s[i-1] = '\n';
        s[i] = '\0';
    }
}

/* reverse Polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP], l[MAX];
    
    while (_getline(l, MAX) > 0) {
        insertnl(l);
        while ((type = getop(s, l)) != EOF && type != '\0') {
            switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                } else {
                    printf("error: zero divisor\n");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }
        }
    }
        
    return 0;
}

#define MAXVAL 100  /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push:  push f onto value stack */
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

/* pop:  pop and return top value from stack */
double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

#define NUMBER '0'

/* dequeue:  removes elements at index 0 ..< i */

void dequeue(char s[], int i) {
    int j = 0;
    while (s[i] != '\0') {
        s[j++] = s[i++];
    }
    s[j] = '\0';
}

/* getop:  get next operator or numeric operand */
int getop(char s[], char l[]) {
    int i, j, c;
    j = 0;

    while ((s[0] = c = l[j++]) == ' ' || c == '\t') { }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        dequeue(l, j);
        return c;    /* not a number */
    }
    i = 0;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = l[j++])) { }
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = l[j++])) { }
    }
    s[i] = '\0';
    if (c != EOF) {
        dequeue(l, --j);
    }
    return NUMBER;
}
