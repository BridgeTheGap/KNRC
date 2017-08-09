#include <stdio.h>
#include <stdlib.h>  /* for atof() */

#define MAXOP  100  /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
double top(void);
double dup(void);
void swap(void);
void clear(void);

/* reverse Polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
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
        case '%':
            op2 = pop();
            if (op2 != 0.0) {
                push(pop() % op2);    
            } else {
                printf("error: modulo by zero\n");
            }
        case '=':
            
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
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

/* top:  print the top value from stack without popping */
double top(void) {
    if (sp > 0) {
        return val[sp-1];
    } else {
        printf("error: stack empty\n");
    }
}

/* dup:  duplicates top element of stack */
double dup(void) {
    if (sp > 0) {
        sp++;
        val[sp] = val[sp-1];
    } else {
        printf("error: stack empty\n");
    }
}

/* swap:  swaps the two topmost elements */
void swap(void) {
    if (sp > 1) {
        double temp = val[sp-1];
        val[sp-1] = val[sp-2];
        val[sp-2] = temp;
    } else {
        printf("error: not enough elements in stack to swap\n");
    }
}

/* clear:  clears stack */
void clear(void) {
    while (sp > 0) {
        val[--sp] = 0;
    }
}