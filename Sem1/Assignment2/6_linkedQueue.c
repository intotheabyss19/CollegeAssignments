/*
6.Write a program to implement a queue with a singly linked Queue, taking the maximum size of the queue as
input from the user. Define the same functions to implement the queue operations as described in Question
no. 4, but do so for a linked Queue instead of an array. Create a menu-based interface, similar to that of
Question no. 4.
*/

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *next;
};

struct node * newNode();
void printQueue(struct node **);
struct node ** CreateNewQueue(int, int);
struct node * newNode();
void add(struct node *, struct node **, int);
void delete(struct node **);

int main()
{
    int choice, number_of_elements, n;
    struct node **firstNodeptr;

    system("clear");

    while (1)
    {
        printf("\nEnter the desired operation:\
                \n\tEnter 1 for creating a new Queue\
                \n\tEnter 2 for printing the Queue\
                \n\tEnter 3 for adding an element to the rear of the Queue\
                \n\tEnter 4 for deleting an element from the front of the Queue\
                \n\tEnter 0 for exiting the program\
                \n\t==> ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Create a new Queue
            printf("\nCreating a new Queue...\n");
            printf("Enter the max size of the Queue: ");
            scanf("%d", &n);
            printf("Enter the number of elements: ");
            scanf("%d", &number_of_elements);
            if(number_of_elements > n)
            {
                printf("Error: Number of elements is greater than the size of stack...\n");
                break;
            }
            firstNodeptr = CreateNewQueue(number_of_elements , n);
            break;
        case 2:
            printf("\nPrinting the Queue...\n");
            printQueue(firstNodeptr);
            break;
        case 3: // Add an element at the rear
            printf("add_at function initiated: \n");
            // if(n = number_of_elements)
            // {
            //     printf("Error: QueueOverflow\n");
            //     break;
            // }
            add(newNode(), firstNodeptr, n);
            number_of_elements++;
            break;
        case 4: // Delete an element from the front
            printf("delete function initiated: \n");
            // if(number_of_elements = 0)
            // {
            //     printf("Error: QueueUnderflow\n");
            //     break;
            // }
            delete(firstNodeptr);
            // number_of_elements--;
            break;
        case 0: // Printing the Queue
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

// Creates a new set of Queue having "n" elements
struct node **CreateNewQueue(int n,int max)
{
    struct node **headptr, *buffer;
    *headptr = newNode();
    for (n; n-1; n--)
    {
        buffer = newNode();
        add(buffer, headptr, max);
    }
    return headptr;
}

// Prints the current Queue
void printQueue(struct node **headptr)
{
    struct node *ii;
    for (ii = *headptr; ii != NULL; ii = ii->next)
        printf("%d\n", ii->key);
}

// Adds a given element to the rear of the current Queue
void add(struct node *bufferNode, struct node **headptr, int max)
{
    struct node *ii = *headptr;
    int i = 0;
    for (i, ii; ii->next!= NULL; ii = ii->next, i++);
    if(i >= max - 1)
    {
        printf("Queue Overflow\n");
        return;
    }
    else
        ii->next = bufferNode;
    return;
}

// Deletes a given element from the Queue from a given position
void delete(struct node **head)
{
    struct node *ii = *head;
    int i = 0;
    if(*head == NULL)
    {
        printf("Queue Underflow\n");
        return;
    }
    else
    {
        *head = (*head) -> next;
        free(ii);
    }
}

//Success