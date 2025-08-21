/*
3. Write a program to implement a stack with an array, taking the maximum size of the stack as input from the user. 
Define functions as described below to implement the stack operations. 
The exact prototypes of the functions are left to the programmer’s discretion.
i) push: Pushes a given element to the stack.
ii) pop: Pops an element from the stack and returns it.
iii) print_stack: Displays the elements of the stack in the correct order beginning from the top.
Create a menu-based interface, similar to that of Question no. 1, where the menu contains the following
options which are self-explanatory: 
i) Create new empty stack, 
ii) Push, 
iii) Pop, 
iv) Count elements,
iv) Print stack, 
v) Quit. 
Note that appropriate messages should be printed for “underflow” and “overflow” conditions.
*/

#include <stdio.h>
#include <stdlib.h>

int * createStack(int, int);
void push(int *, int, int);
int pop(int *);
int countElements(int *);
void printStack(int *, int);

int main()
{
    int choice, size, numElements, *stack, element;
    system("clear");
    while (1)
    {
        printf("\nEnter the desired operation:\
                \n\tEnter 1 for creating a new stack\
                \n\tEnter 2 for printing the stack\
                \n\tEnter 3 for pushing an element into the stack\
                \n\tEnter 4 for popping an element from the stack\
                \n\tEnter 5 for counting the elements of the stack\
                \n\tEnter 0 for quitting the program\
                \n\t==> ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Create a new stack
            printf("\nCreating a new stack...\n");
            printf("Enter the Max Size of the Stack: ");
            scanf("%d", &size);
            printf("\nEnter the number of elements you want to add to the stack?: \n==>");
            scanf("%d", &numElements);
            if(numElements > size)
            {
                printf("StackOverflow Error: The number of elements can't be greater than the max size");
                break;
            }
            stack = createStack(size, numElements);
            break;
        case 2:
            printf("\nPrinting the stack...\n");
            printStack(stack, numElements);
            break;
        case 3: // Add an element at the rear
            printf("push function initiated: \n");
            printf("Enter an element: \n\t==>");
            scanf("%d", &element);
            push(stack, size, element);
            break;
        case 4: // Delete an element from the rear
            printf("pop function initiated: \n");
            printf("The deleted element is %d\n", pop(stack));    
            break;
        case 5: // Count elements
            printf("The number of elements is %d\n", countElements(stack));
            break;
        case 0:
            printf("\nExiting the Program...\n");
            return 0;
        default:
            printf("\nPlease choose a valid option: \n");
            break;
        }
    }
    return 0;
}

int * createStack(int s, int n)
{
    int i, *arr = calloc(s, sizeof(int));
    printf("Enter the elements of the stack: \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    return arr;
}

void printStack(int * stk, int num)
{
    int i=0;
    while(stk[i])
    {
        printf("%d\n", stk[i]);
        i++;
    }
    printf("Array printed Successfully\n");
}

int countElements(int *stk)
{
    int count = 0;
    while(stk[count])
        count++;
    return count;
}

void push(int *stk, int max, int element)
{
    int i = countElements(stk);
    if(i > max)
    {
        printf("StackOverflow Error: The stack is already full.\n");
        return;
    }
    for(i ; i ; i--)
        stk[i]=stk[i-1];
    stk[0]=element;
}

int pop(int *stk)
{
    int i = countElements(stk), buffer = stk[0], j;
    for(j = 0; j < i; j++)
        stk[j] = stk[j+1];
    return buffer;
}

// Success