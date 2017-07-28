#include <stdio.h>

#define MAX_INPUT_LENGTH        10000

#define NORMAL      0
#define SINGLE_QUOTE    1
#define DOUBLE_QUOTE    2
#define SLASH       3
#define MULTI_COMMENT   4
#define INLINE_COMMENT  5
#define STAR        6

int state_from_normal(char symbol, char prev_symbol)
{
    int state = NORMAL;

    if (symbol == '\'' && prev_symbol != '\\')
        state = SINGLE_QUOTE;
    else if (symbol == '"')
        state = DOUBLE_QUOTE;
    else if (symbol == '/')
        state = SLASH;

    return state;
}

int state_from_single_quote(char symbol, char prev_symbol, char pre_prev_symbol)
{
    int state = SINGLE_QUOTE;

    if (symbol == '\'' && (prev_symbol != '\\' || pre_prev_symbol == '\\'))
        state = NORMAL;

    return state;
}

int state_from_double_quote(char symbol, char prev_symbol, char pre_prev_symbol)
{
    int state = DOUBLE_QUOTE;

    if (symbol == '"' && (prev_symbol != '\\' || pre_prev_symbol == '\\'))
        state = NORMAL;

    return state;
}

int state_from_slash(char symbol)
{
    int state = SLASH;

    if (symbol == '*')
        state = MULTI_COMMENT;
    else if (symbol == '/')
        state = INLINE_COMMENT;
    else
        state = NORMAL;

    return state;
}

int state_from_multi_comment(char symbol)
{
    int state = MULTI_COMMENT;

    if (symbol == '*')
        state = STAR;

    return state;
}

int state_from_star(char symbol)
{
    int state = STAR;

    if (symbol == '/')
        state = NORMAL;
    else if (symbol != '*')
        state = MULTI_COMMENT;

    return state;
}

int state_from_inline_comment(char symbol)
{
    int state = INLINE_COMMENT;

    if (symbol == '\n')
        state = NORMAL;

    return state;
}

int state_from(int prev_state, char symbol, char prev_symbol, char pre_prev_symbol)
{
    if (prev_state == NORMAL)
        return state_from_normal(symbol, prev_symbol);
    else if (prev_state == SINGLE_QUOTE)
        return state_from_single_quote(symbol, prev_symbol, pre_prev_symbol);
    else if (prev_state == DOUBLE_QUOTE)
        return state_from_double_quote(symbol, prev_symbol, pre_prev_symbol);
    else if (prev_state == SLASH)
        return state_from_slash(symbol);
    else if (prev_state == MULTI_COMMENT)
        return state_from_multi_comment(symbol);
    else if (prev_state == INLINE_COMMENT)
        return state_from_inline_comment(symbol);
    else if (prev_state == STAR)
        return state_from_star(symbol);
    else
        return -1;
}

char opening_symbol(char symbol)
{
    if (symbol == ')')
        return '(';
    else if (symbol == ']')
        return '[';
    else if (symbol == '}')
        return '{';
    else
        return '\0';
}

int is_valid_closing(char symbol, char nests[], int nest_index)
{
    return nest_index > 0 && nests[nest_index-1] == opening_symbol(symbol);
}

int main(void)
{
    char nests[MAX_INPUT_LENGTH] = { '\0' };
    int  nest_index = 0;

    char input;
    char symbol = '\0';
    char prev_symbol = '\0';
    char pre_prev_symbol;

    int state = NORMAL;
    int prev_state;

    int line = 1, column = 0;

    while ((input = getchar()) != EOF) {
        column++;

        pre_prev_symbol = prev_symbol;
        prev_symbol     = symbol;
        symbol          = input;

        prev_state = state;
        state = state_from(prev_state, symbol, prev_symbol, pre_prev_symbol);

        if (symbol == '\n') {
            line++;
            column = 0;
        } else if (state == NORMAL) {
            if (symbol == '(' || symbol == '[' || symbol == '{') {
                nests[nest_index++] = symbol;
            }
            if (symbol == ')' || symbol == ']' || symbol == '}') {
                if (is_valid_closing(symbol, nests, nest_index)) {
                    nests[--nest_index] = '\0';
                } else {
                    printf("Unexpected '%c' at line %d, column %d\n", symbol, line, column);
                    return 1;
                }
            }
        }
    }

    if (nest_index > 0) {
        printf("Unbalanced '%c'", nests[0]);
        for (int i = 1; i < nest_index; i++) {
            printf(", '%c'", nests[i]);
        }
        printf("\n");
        return 1;
    } else {
        printf("Balanced\n");
    }
}
