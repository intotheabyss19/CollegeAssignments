/*3.Write a program to implement a queue with an array, assuming that it is a linear queue. Given below are
abstract definitions of operations that need to be implemented by writing a function for each operation,
where q is a queue, x is an element that can be stored in q, front is the end of queue where only the delete
operation is allowed, rear is the other end of the queue where only the add operation is allowed. After
initially creating a queue q with k elements and with maximum size max, taking k, max, and the elements
of q as input from the user, your program will show a menu-based interface, similar to Question no. 2,
where the user can choose from the following options: i) Add, ii) Delete, iii) Display, iv) Quit. The menu
will be displayed repeatedly until the user chooses option (iv). The Add and Delete functions must call the
functions IsFull and IsEmpty, respectively, to check the overflow and underflow conditions, for which
appropriate messages should be displayed. Your program should be able to perform the Add operation as
long as there is empty space available in the array. Do not use any external variable.
IsEmpty(q) := returns True if q is empty, otherwise returns False.

IsFull(q) := returns True if q is full, otherwise returns False.
Add(q, x) := adds x to the rear of q.
Delete(q) := deletes an element x from the front of q and returns x.
Display(q) := prints all elements of q in the order starting from front and ending at rear.*/


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

int Display(int queue[] , int *k)
{
    if(IsEmpty(k))
    {
        printf("Empty queue []");
        return -1;
    }

    for(int i = 0; i < *k; i++)
        printf("%d ", queue[i]);
    printf("\n\n");

    return 0;
}

int Delete(int queue[] , int *k)
{
    if(IsEmpty(k))
    {
        printf("Error: Queue Underflow\n");
        return -1;
    }

    int i = 0, x = queue[i];

    for(; i < *k; i++)
        queue[i] = queue[i+1];

    (*k)--;
    
    return x;
}

int Add(int queue[], int x, int *k)
{
    if(IsFull(k))
    {
        printf("Error: Queue Overflow\n");
        return -1;
    }

    queue[*k] = x;
    (*k)++;

    return 1;
}

int main()
{
    int k = -1, ch = 0, x;
    printf("Enter the size of the queue: ");
    scanf("%d", &k);

    int queue[MAXLENGTH];

    printf("Enter the queue: \n");
    for(int i = 0; i < k; i++)
        scanf("%d", &queue[i]);
    
    do{
        printf("\nSelect an operation:\n\
                Enter '1' to Add an element to the Queue\n\
                Enter '2' to Delete an element from the Queue\n\
                Enter '3' to Display the Queue\n\
                Enter '4' to Quit\n\t==> ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                printf("\nEnter the element: ");
                scanf("%d", &x);

                if(Add(queue, x, &k) == 1)
                {
                    printf("The queue after Add operation is: ");
                    Display(queue, &k);
                }

                break;

            case 2:
                int x = Delete(queue, &k) != -1;
                if(x)
                {
                    printf("The popped element is: %d\n", x);
                    printf("The Queue after Delete operation is: ");
                    Display(queue, &k);
                }

                break;
            
            case 3:
                printf("The Queue is: ");
                Display(queue, &k);
                break;

            default: break;
        }
    }while(ch != 4);

    printf("Exiting the Program\n");
    return 0;
}