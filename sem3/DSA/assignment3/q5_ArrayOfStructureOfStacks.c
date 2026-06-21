/*5.Write a program to implement a series of n stacks with an array of structures where each instance of a
structure represents one stack (hint: declare a stack, its top, and its maximum size as the members of the
structure), and the stacks are indexed with the numbers 1 to n, i.e. the ith stack has index number i. The
maximum size of the ith stack is denoted by maxi. After taking the value of n and the n values of maxi as
input from the user, the program will display elegantly the contents of the n stacks (which are initially
empty) along with a menu which will have the following options: i) Push, ii) Pop, iii) Transfer_Next, iv)
Transfer_Anywhere, v) Quit. The contents of the n stacks along with the menu will be displayed repeatedly
in a loop until the user chooses to quit. The abstract definitions of the four operations for the menu options
(i) to (iv) respectively are given below, where S is a series of n stacks, and x is an element that can be
stored in a stack. Do not use any external variable. The data type of the elements of the stacks are left to
the programmer’s discretion.
Push(x, S) := pushes x to the 1st stack of S.
Pop(S) := pops an element x from the nth stack of S and returns x.
Transfer_Next(i) := pops an element x from the ith stack of S and pushes x to the (i+1)th stack of S.
Transfer_Anywhere(i, j) := pops an element x from the ith stack of S and pushes x to the jth stack of S*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSTACKSIZE 10

typedef struct stack{
    int stack[MAXSTACKSIZE];
    int top;
    int maxSize;
}Stack;

int IsEmpty(int *k)
{
    if((*k) < 0)
        return 1;
    return 0;
}

int IsFull(int *k, int max)
{
    if((*k) >= max)
        return 1;
    return 0;
}

int Display(Stack *Stacks, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("Stack %d: ", i + 1);
        if(IsEmpty(&Stacks[i].top))
        {
            printf("Empty stack []");
        }
        else
        {
            for(int j = Stacks[i].top - 1; j >= 0; j--)
                printf("%d ", Stacks[i].stack[j]);
        }
        printf("\n\n");
    }
    return 0;
}

int Pop(Stack *Stacks, int n)
{
    if(IsEmpty(&Stacks[n - 1].top))
    {
        printf("Error: Stack Underflow\n");
        return -1; 
    }

    int x = Stacks[n - 1].stack[Stacks[n - 1].top - 1];
    Stacks[n - 1].top--;
    return x;
}

int Push(Stack *Stacks, int x, int n)
{
    if(IsFull(&Stacks[0].top, Stacks[0].maxSize))
    {
        printf("Error: Stack Overflow\n");
        return -1;
    }

    Stacks[0].stack[Stacks[0].top] = x;
    Stacks[0].top++;

    return 1;
}

int Transfer_Next(Stack *Stacks, int i, int n)
{
    if(i < 1 || i >= n)
    {
        printf("Error: Invalid stack index\n");
        return -1;
    }

    if(IsEmpty(&Stacks[i - 1].top))
    {
        printf("Error: Stack Underflow\n");
        return -1; 
    }

    int x = Stacks[i - 1].stack[Stacks[i - 1].top - 1];
    Stacks[i - 1].top--;

    if(IsFull(&Stacks[i].top, Stacks[i].maxSize))
    {
        printf("Error: Stack Overflow\n");
        Stacks[i - 1].top++;
        return -1;
    }

    Stacks[i].stack[Stacks[i].top] = x;
    Stacks[i].top++;

    return 1;
}

int Transfer_Anywhere(Stack *Stacks, int i, int j, int n)
{
    if(i < 1 || i > n || j < 1 || j > n)
    {
        printf("Error: Invalid stack index\n");
        return -1;
    }

    if(i == j)
    {
        printf("Error: Source and destination stacks are the same\n");
        return -1;
    }

    if(IsEmpty(&Stacks[i - 1].top))
    {
        printf("Error: Stack Underflow\n");
        return -1; 
    }

    int x = Stacks[i - 1].stack[Stacks[i - 1].top - 1];
    Stacks[i - 1].top--;

    if(IsFull(&Stacks[j - 1].top, Stacks[j - 1].maxSize))
    {
        printf("Error: Stack Overflow\n");
        Stacks[i - 1].top++;
        return -1;
    }

    Stacks[j - 1].stack[Stacks[j - 1].top] = x;
    Stacks[j - 1].top++;

    return 1;
}

int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    Stack *Stacks = calloc(n, sizeof (Stack));

    for(int i = 0; i < n; i++)
    {
        printf("Enter max size for stack %d: ", i + 1);
        scanf("%d", &Stacks[i].maxSize);
        Stacks[i].top = -1;
    }

    int choice;
    while(1)
    {
        Display(Stacks, n);
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Transfer Next\n");
        printf("4. Transfer Anywhere\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int x;
                printf("Enter element to push: ");
                scanf("%d", &x);
                Push(Stacks, x, n);
                break;
            }
            case 2:
            {
                printf("Popped element: %d\n", Pop(Stacks, n));
                break;
            }
            case 3:
            {
                int i;
                printf("Enter stack index: ");
                scanf("%d", &i);
                Transfer_Next(Stacks, i, n);
                break;
            }
            case 4:
            {
                int i, j;
                printf("Enter source stack index: ");
                scanf("%d", &i);
                printf("Enter destination stack index: ");
                scanf("%d", &j);
                Transfer_Anywhere(Stacks, i, j, n);
                break;
            }
            case 5:
            {
                free(Stacks);
                return 0;
            }
            default:
            {
                printf("Invalid choice\n");
            }
        }
    }
}