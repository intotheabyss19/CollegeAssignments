#/* 9. Write a program to solve the valid parentheses problem. Take an infix expression with brackets as input
from the user through the command line where each token of the infix expression is entered as a
command-line argument in the correct order, as shown in the sample execution given below (the tokens are
separated by blank spaces). If the brackets in the expression are correctly matched, then your program
reports that it is a valid expression, otherwise your program reports that it is an invalid expression. Assume
that all three types of brackets—parentheses/round brackets, braces/curly brackets, and square brackets—
are allowed in the entered infix expression.
Sample Execution
$ ./check_brackets.out a + [ b * ( c – d / { e – f ) + g ] / h } ↵
Invalid expression (brackets not matched).
Page 3 of 5$ ./check_brackets.out a + [ b * { c – d / ( e – f ) + g } / h ] ↵
Valid expression (brackets are matched). */

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Stack structure
typedef struct {
    char items[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, char item) {
    if (s->top < MAX - 1) {
        s->items[++s->top] = item;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top--];
    }
    return '\0';
}

// Function to check if characters match as a valid bracket pair
int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// Function to check if an expression has valid bracket matching
int checkBrackets(char *expression) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(&stack, ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&stack) || !isMatchingPair(pop(&stack), ch)) {
                return 0; // Brackets do not match
            }
        }
    }
    return isEmpty(&stack); // Valid if stack is empty
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <expressions>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (checkBrackets(argv[i])) {
            printf("Expression %d: %s - Valid\n", i, argv[i]);
        } else {
            printf("Expression %d: %s - Invalid\n", i, argv[i]);
        }
    }
    return 0;
}
