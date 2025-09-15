/*
2. Modify your program from Question no. 1 to add a function to delete a node from the linked list; define the
function as described below. Add to your menu an option called “Delete from position” which is self-
explanatory.
i) delete_from_position: Deletes a node from a given position in the list, i.e. if the given position is p,
then the pth node is removed from the list and then destroyed (i.e. the storage held by the deleted node
should be freed).
*/

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *next;
};

struct node * newNode();
void printList(struct node **);
struct node ** CreateNewList(int);
struct node * newNode();
struct node ** add_at_front(struct node *, struct node **);
void add_at_rear(struct node *, struct node **);
struct node ** insert_at_position(struct node *, struct node **);
void delete_at_position(struct node **);

int main()
{
    int choice, number_of_elements, n;
    struct node **firstNodeptr;

    system("clear");

    while (1)
    {
        printf("\nEnter the desired operation:\
                \n\tEnter 1 for creating a new list\
                \n\tEnter 2 for printing the list\
                \n\tEnter 3 for adding an element to the front of the list\
                \n\tEnter 4 for adding an element to the rear of the list\
                \n\tEnter 5 for adding an element to a given position\
                \n\tEnter 6 for deleting an element from a given position\
                \n\tEnter 0 for exiting the program\
                \n\t==> ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Create a new list
            printf("\nCreating a new list...\n");
            printf("Enter the number of elements: ");
            scanf("%d", &number_of_elements);
            firstNodeptr = CreateNewList(number_of_elements);
            break;
        case 2:
            printf("\nPrinting the list...\n");
            printList(firstNodeptr);
            break;
        case 3: // Add an element at the front
            printf("add_at_front function initiated: \n");
            firstNodeptr = add_at_front(newNode(), firstNodeptr);
            break;
        case 4:
            printf("add_at_rear function initiated: \n");
            add_at_rear(newNode(), firstNodeptr);
            break;
        case 5:
            printf("insert_at_position function initiated: \n");
            firstNodeptr = insert_at_position(newNode(), firstNodeptr);
            break;
        case 6:
            printf("delete_at_position function initiated: \n");
            delete_at_position(firstNodeptr);
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

// Creates a new set of linked list having "n" elements
struct node **CreateNewList(int n)
{
    struct node **headptr, *buffer;
    *headptr = newNode();
    for (n; n-1; n--)
    {
        buffer = newNode();
        add_at_rear(buffer, headptr);
    }
    return headptr;
}

// Prints the current linked list
void printList(struct node **headptr)
{
    struct node *ii;
    for (ii = *headptr; ii != NULL; ii = ii->next)
        printf("%d ==> ", ii->key);
    printf("NULL\n");
}

// Adds a given element to the front of the current linked list
struct node ** add_at_front(struct node *newNode, struct node **headptr)
{
    struct node * buffer = *headptr;
    newNode->next = *headptr;
    *headptr = newNode;
    return headptr;
}

// Adds a given element to the rear of the current linked list
void add_at_rear(struct node *bufferNode, struct node **headptr)
{
    struct node *ii;
    for (ii = *headptr; ii->next != NULL; ii = ii->next);
    ii->next = bufferNode;
    return;
}

// Adds a given element at a given position
struct node ** insert_at_position(struct node *bufferNode, struct node **head)
{
    int i, n;
    struct node *ii;
    printf("Enter a position: ");
    scanf("%d", &n);
    for (ii = *head, i = 0; ii!=NULL ; i++, ii = ii->next);
    if(n>i+1)
    {
        printf("\nEOL ERROR: The entered position is greater than number of elements...\n");
        return head;
    }
    for (ii = *head, i = 0; i < n - 2; i++, ii = ii->next);
    bufferNode->next = ii->next;
    ii->next = bufferNode;
    return head;
}

// Deletes a given element from the linked list from a given position
void delete_at_position(struct node **head)
{
    int i, pos;
    struct node *ii, *buffer;
    buffer = *head;
    printf("Enter the position you want to delete: ");
    scanf("%d", &pos);
    if(pos == 1)
    {
        ii = *head;
        buffer = *head;
        ii = ii->next;
        *head = ii;
        free(buffer);
        return;
    }
    for(ii = *head, i = 1; i<pos-1; i++, ii = ii->next);
    buffer = ii -> next;
    ii->next = buffer->next;
    free(buffer);
}
//Success