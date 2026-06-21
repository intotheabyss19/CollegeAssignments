/*
13. Write a program to transform an infix expression, with brackets, into a postfix expression. Take the infix
expression as input from the user as command-line arguments where each token of the infix expression is
entered as a command-line argument in the correct order, as shown in the sample execution given below
(the tokens are separated by blank spaces). Your program will print the equivalent postfix expression as the
final output. Assume that only the five operators ‘+’, ‘-‘, ‘*’, ‘/’, ‘%’ are allowed in the infix expression,
that any real number or variable (denoted by letters from the English alphabet) is allowed as an operand in
the expression, and that brackets (parentheses, braces, and square brackets) are allowed in the expression.
The aforementioned five operators have their usual meaning, precedences, and associativity rules (as in C
programming language).

Sample Execution
$ ./infix_to_postfix.out a * [ b + { ( c – d ) / e + f } * g ] – h ↵
a b c d – e / f + g * + * h –
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void push(char *stack, int *top, char x) {
    if (*top < MAX - 1) {
        (*top)++;
        stack[*top] = x;
    }
}

char pop(char *stack, int *top) {
    if (*top == -1) return -1;
    return stack[(*top)--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int is_operand(char *token) {
    char c = token[0];
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

int is_open_bracket(char c) {
    return c == '(' || c == '{' || c == '[';
}

int is_close_bracket(char c) {
    return c == ')' || c == '}' || c == ']';
}

char match_bracket(char c) {
    if (c == ')') return '(';
    if (c == '}') return '{';
    if (c == ']') return '[';
    return '\0';
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("Usage: This program utilizes command line arguments\n");
        printf("\teg: ./filename <Postfix Expression>\n\tNote: Use \\* for multiplication & \\(, \\) for curve brackets\n");
        return 1;
    }
    char stack[MAX];
    int top = -1;

    for (int i = 1; i < argc; i++) {
        char *token = argv[i];
        char c = token[0];

        if (is_operand(token)) {
            printf("%c ", c);
        } else if (is_open_bracket(c)) {
            push(stack, &top, c);
        } else if (is_close_bracket(c)) {
            while (top != -1 && stack[top] != match_bracket(c)) {
                printf("%c ", pop(stack, &top));
            }
            if (top != -1 && stack[top] == match_bracket(c)) {
                pop(stack, &top);  // Pop the matching open bracket
            }
        } else if (is_operator(c)) {
            while (top != -1 && precedence(stack[top]) >= precedence(c) && !is_open_bracket(stack[top])) {
                printf("%c ", pop(stack, &top));
            }
            push(stack, &top, c);
        } else {
            printf("Error: Invalid token '%s'\n", token);
            return 1;
        }
    }

    // Pop remaining operators in the stack
    while (top != -1) {
        if (is_open_bracket(stack[top])) {
            printf("Error: Mismatched brackets\n");
            return 1;
        }
        printf("%c ", pop(stack, &top));
    }
    printf("\n");
    return 0;
}

