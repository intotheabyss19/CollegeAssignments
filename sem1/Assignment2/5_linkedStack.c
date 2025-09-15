/*
5. Write a program to implement a stack with a singly linked list, taking the maximum size of the stack as
input from the user. Define the same functions to implement the stack operations as described in Question
no. 3, but do so for a linked list instead of an array. Create a menu-based interface, similar to that of
Question no. 3.
*/

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *next;
};

struct node * newNode(); // done
void printStack(struct node **);
struct node ** CreateNewStack(int);
struct node * newNode();
struct node ** push(struct node *, struct node **);
void pop(struct node **);

int main()
{
    int choice, number_of_elements, n;
    struct node **firstNodeptr;

    system("clear");

    while (1)
    {
        printf("\nEnter the desired operation:\
                \n\tEnter 1 for creating a new stack\
                \n\tEnter 2 for printing the stack\
                \n\tEnter 3 for pushing an element\
                \n\tEnter 4 for popping an element\
                \n\tEnter 0 for exiting the program\
                \n\t==> ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Create a new list
            printf("\nCreating a new stack...\n");
            printf("Enter the max size of the stack: ");
            scanf("%d", &n);
            printf("Enter the number of elements: ");
            scanf("%d", &number_of_elements);
            if(number_of_elements > n)
            {
                printf("Error: Number of elements is greater than the size of stack...\n");
                break;
            }
            firstNodeptr = CreateNewStack(number_of_elements);
            break;
        case 2: // Printing the stack
            printf("\nPrinting the stack...\n");
            printStack(firstNodeptr);
            break;
        case 3: // Add an element at the front
            printf("push function initiated: \n");
            if(n = number_of_elements)
            {
                printf("Error: StackOverflow\n");
                break;
            }
            firstNodeptr = push(newNode(), firstNodeptr);
            number_of_elements++;
            break;
        case 4: // Removing the element at the front
            printf("pop function initiated: \n");
            if(number_of_elements = 0)
            {
                printf("Error: StackUnderflow\n");
                break;
            }
            pop(firstNodeptr);
            number_of_elements--;
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

// Creates a new node whenever called and returns the address to the newly created node
struct node *newNode()
{
    struct node *newNode = malloc(sizeof(struct node));
    int *n = malloc(sizeof(int));
    printf("\nEnter a value: ");
    scanf("%d", n);
    newNode->key = *n;
    newNode->next = NULL;
    return newNode;
}

// Creates a new stack having "n" elements
struct node **CreateNewStack(int n)
{
    struct node **headptr, *buffer;
    *headptr = newNode();
    for (n; n-1; n--)
    {
        buffer = newNode();
        push(buffer, headptr);
    }
    return headptr;
}

// Prints the current stack
void printStack(struct node **headptr)
{
    struct node *ii;
    for (ii = *headptr; ii != NULL; ii = ii->next)
        printf("%d\n", ii->key);
}

// Adds a given element to the front of the stack
struct node ** push(struct node *newNode, struct node **headptr)
{
    struct node * buffer = *headptr;
    newNode->next = *headptr;
    *headptr = newNode;
    return headptr;
}

// Deletes the front element from the stack
void pop(struct node **head)
{
    int i;
    struct node *ii, *buffer = *head;
    ii = *head;
    buffer = *head;
    ii = ii->next;
    *head = ii;
    printf("The deleted element is %d\n", buffer -> key);
    free(buffer);
    return;
}

// Success