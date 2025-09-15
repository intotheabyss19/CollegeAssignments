/*4. Write a program to implement a queue with an array, taking the maximum size of the queue as input from
the user. Define functions as described below to implement the queue operations. The exact prototypes of
the function are left to the programmer’s discretion.
i) add: Adds a given element to the queue.
ii) delete: Removes an element from the queue and returns it.
iii) print_queue: Displays the element of the queue in the correct order from front to rear.
Create a menu-based interface, similar to that of Question no. 3, where the menu contains the following
options which are self-explanatory: i) Create new empty queue, ii) Add, iii) Delete, iv) Count elements,
iv) Print queue, v) Quit. Note that appropriate messages should be printed for “underflow” and “overflow”
conditions.*/

#include <stdio.h>
#include <stdlib.h>

int * createQueue(int, int);
void add(int *, int, int);
int delete(int *);
int countElements(int *);
void printQueue(int *, int);

int main()
{
    int choice, size, numElements, *queue, element;
    system("clear");
    while (1)
    {
        printf("\nEnter the desired operation:\
                \n\tEnter 1 for creating a new queue\
                \n\tEnter 2 for printing the queue\
                \n\tEnter 3 for pushing an element into the queue\
                \n\tEnter 4 for popping an element from the queue\
                \n\tEnter 5 for counting the elements of the queue\
                \n\tEnter 0 for quitting the program\
                \n\t==> ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Create a new queue
            printf("\nCreating a new queue...\n");
            printf("Enter the Max Size of the Queue: ");
            scanf("%d", &size);
            printf("\nEnter the number of elements you want to add to the queue?: \n==>");
            scanf("%d", &numElements);
            if(numElements > size)
            {
                printf("StackOverflow Error: The number of elements can't be greater than the max size");
                break;
            }
            queue = createQueue(size, numElements);
            break;
        case 2:
            printf("\nPrinting the queue...\n");
            printQueue(queue, countElements(queue));
            break;
        case 3: // Add an element at the rear
            printf("add function initiated: \n");
            printf("Enter an element: \n\t==>");
            scanf("%d", &element);
            add(queue, size, element);
            break;
        case 4: // Delete an element from the front
            printf("delete function initiated: \n");
            printf("The deleted element is %d\n", delete(queue));    
            break;
        case 5: // Count elements
            printf("The number of elements is %d\n", countElements(queue));
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

int * createQueue(int s, int n)
{
    int i, *arr = calloc(s, sizeof(int));
    printf("Enter the elements of the stack: \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    return arr;
}

void printQueue(int * queue, int num)
{
    int i=0;
    while(queue[i])
    {
        printf("%d\n", queue[i]);
        i++;
    }
    printf("Array printed Successfully\n");
}

int countElements(int *queue)
{
    int count = 0;
    while(queue[count])
        count++;
    return count;
}

void add(int *queue, int max, int element)
{
    int i = countElements(queue);
    if(i > max)
    {
        printf("QueueOverflow Error: The queue is already full.\n");
        return;
    }
    queue[i]=element;
}

int delete(int *queue)
{
    int i = countElements(queue), buffer = queue[0], j;
    for(j = 0; j < i; j++)
        queue[j] = queue[j+1];
    return buffer;
}
