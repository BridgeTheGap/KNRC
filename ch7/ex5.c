#include <stdio.h>

void push(double);
double pop(void);

int main() {
    char c;
    double f, op;
    
    while (1) {
        if (scanf("%lf", &f) == 1) {
            push(f);
        } else if (scanf("%c", &c) == 1) {
            switch (c) {
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op = pop();
                push(pop() - op);
                break;
            case '/':
                op = pop();
                if (op != 0.0) {
                    push(pop() / op);
                } else {
                    printf("error: zero divisor\n");
                    return 0;
                }
                break;
            default:
                printf("error: unknown command %c\n", c);
                return 0;
            }

            if (getchar() == '\n') {
                printf("\t%.8g\n", pop());
            }
        } else {
            return 0;
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