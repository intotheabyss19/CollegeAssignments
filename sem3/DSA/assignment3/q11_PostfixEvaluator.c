/*
 * 11. Write a program to evaluate an expression written in the postfix notation where the tokens (i.e. the
operands and the operators) of the expression are entered by the user as command-line arguments. Each
token (an operator or an operand) will be separated from another token by a blank space at the command
line, i.e. each token is a command-line argument. Your program should display the result of the expression
as the final output. Assume that only the five operators ‘+’, ‘-‘, ‘*’, ‘/’, ‘%’ are allowed in the postfix
expression, and that only integers are allowed as operands in the expression. The aforementioned five
operators have their usual meaning, precedences, and associativity rules (as in C programming language).
Sample Execution
$ ./evaluate_postfix.out 15 17 10 * + 150 3 / 20 % - 5 15 * + ↵
Result: 250
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

void push(int stack[], int *top, int x) 
{
    if (*top < MAXSIZE - 1) {
        stack[++(*top)] = x;  // Push the actual value x, not '*'
    } else {
        printf("Stack Overflow\n");
        exit(1);
    }
}

int pop(int stack[], int *top) 
{
    if (*top >= 0) {
        return stack[(*top)--];
    } else {
        printf("Stack Underflow\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) 
{
    int stack[MAXSIZE];
    int top = -1;

    if (argc < 2) 
    {
        printf("Usage: This program utilizes command line arguments\n");
        printf("\teg: ./filename <Postfix Expression>\n\tNote: Use \\* for multiplication\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char *token = argv[i];
        if (token[0] >= '0' && token[0] <= '9') {
            push(stack, &top, atoi(token));
        } 
        else if ((token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '%') && token[1] == '\0')
        {
            if (top < 1) 
            {
                printf("Error: Not enough operands\n");
                return 1;
            }

            int b = pop(stack, &top);
            int a = pop(stack, &top);
            switch (token[0]) {
                case '+': push(stack, &top, a + b); break;
                case '-': push(stack, &top, a - b); break;
                case '*': push(stack, &top, a * b); break;
                case '/': 
                    if (b == 0) {
                        printf("Error: Don't Divide by zero\n");
                        return 1;
                    }
                    push(stack, &top, a / b); 
                    break;
                case '%': 
                    if (b == 0) {
                        printf("Error: Modulo operation by zero\n");
                        return 1;
                    }
                    push(stack, &top, a % b); 
                    break;
            }
        }
        else
        {
            printf("Error: Token is Invalid '%s'\n", token);
            return 1;
        }
    }

    if (top != 0) {
        printf("Error: Too many operands\n");
        return 1;
    }

    printf("Result: %d\n", pop(stack, &top));
    return 0;
}
