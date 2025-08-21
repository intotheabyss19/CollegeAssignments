/*
2.Write a program to implement a stack with an array. Given below are abstract definitions of operations that
need to be implemented by writing a function for each operation, where s is a stack, x is an element that
can be stored in s, top is the end of stack where push and pop operations are allowed, bottom is the other
end of the stack. After initially creating a stack s with k elements and with maximum size max, taking k,
max, and the elements of s as input from the user, your program will show a menu-based interface, similar
to Question no. 1, where the user can choose from the following options: i) Push, ii) Pop, iii) Display,
iv) Quit. The menu will be displayed repeatedly until the user chooses option (iv). The Push and Pop
functions must call the functions IsFull and IsEmpty, respectively, to check the overflow and underflow
conditions, for which appropriate messages should be displayed. Do not use any external variable.
IsEmpty(s) := returns True if s is empty, otherwise returns False.
IsFull(s) := returns True if s is full, otherwise returns False.
Push(s, x) := pushes x to s.
Pop(s) := pops an element x from s and returns x.
Display(s) := prints all elements of s in the order starting from top and ending at bottom.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 5

int IsEmpty(int *k)
{
    if((*k) < 0)
        return 1;
    return 0;
}

int IsFull(int *k)
{
    if((*k) >= MAXLENGTH)
        return 1;
    return 0;
}

int Display(int stack[] , int *k)
{
    if(IsEmpty(k))
    {
        printf("Empty stack []");
        return -1;
    }

    for(int i = *k - 1; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n\n");

    return 0;
}

int Pop(int stack[] , int *k)
{
    if(IsEmpty(k))
    {
        printf("Error: Stack Underflow\n");
        return -1; 
    }

    int x = stack[*k - 1];
    (*k)--;
    return x;
}

int Push(int stack[], int x, int *k)
{
    if(IsFull(k))
    {
        printf("Error: Stack Overflow\n");
        return -1;
    }

    stack[*k] = x;
    (*k)++;

    return 1;
}

int main()
{
    int k = -1, ch = 0, x;
    printf("Enter the size of the Stack: ");
    scanf("%d", &k);

    int stack[MAXLENGTH];

    printf("Enter the stack: \n");
    for(int i = 0; i < k; i++)
        scanf("%d", &stack[i]);
    
    do{
        printf("\nSelect an operation:\n\
                Enter '1' to Push an element to the stack\n\
                Enter '2' to Pop an element from the stack\n\
                Enter '3' to Display the stack\n\
                Enter '4' to Quit\n\t==> ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                printf("\nEnter the element: ");
                scanf("%d", &x);

                if(Push(stack, x, &k) == 1)
                {
                    printf("The stack after Push operation is: ");
                    Display(stack, &k);
                }

                break;
            
            case 2:
                int x = Pop(stack, &k) != -1;
                if(x)
                {
                    printf("The popped element is: %d\n", x);
                    printf("The stack after Pop operation is: ");
                    Display(stack, &k);
                }

                break;
            
            case 3:
                printf("The stack is: ");
                Display(stack, &k);
                break;

            default: break;
        }
    }while(ch != 4);

    printf("Exiting the Program\n");
    return 0;
}
