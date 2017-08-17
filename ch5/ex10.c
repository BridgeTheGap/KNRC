#include <stdio.h>

#define MAXOP 50
#define NUMBER '0'

int getop(char *, double *);
void push(double);
double pop(void);

/* expr:  evaluates a reverse Polish expression */
int main(int argc, char *argv[]) {
    int type;
    double op2, num;
    while (--argc > 0) {
        switch((type = getop(*++argv, &num))) {
        case NUMBER:
            push(num);
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
            break;
        default:
            printf("error: unknown command %s\n", *argv);
            goto End;
        }
    }
    printf("%.8g\n", pop());
        
    End: ;
    return 0;
}

#include <ctype.h>

/* getop:  get next operator or numeric operand */
int getop(char *s, double *num) {
    int i, c;
    for (*num = 0.0; isdigit((c = *s)); s++) {
        *num = *num * 10 + (double)c - '0';
    }
    switch (c) {
    case '.': {
        double d = 1.0;
        while (isdigit((c = *++s))) {
            *num = *num * 10 + c - '0';
            d *= 10.0;
        }
        
        if (c == '\0') {
            *num /= d;
            return NUMBER;
        } else {
            return -1;
        }
    }
    case EOF: case '\0':
        return NUMBER;
    default:
        return *num == 0.0 ? c : -1;    /* not a number */
    }    
}

static double op[MAXOP];
static int sp = 0;

/* push:  push f onto value stack */
void push(double f) {
    if (sp < MAXOP) {
        op[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

/* pop:  pop and return top value from stack */
double pop(void) {
    if (sp > 0) {
        return op[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

