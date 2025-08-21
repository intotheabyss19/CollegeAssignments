/*4.Similar to Question no. 3 above, write a program to implement a circular queue with an array. All other
requirements remain the same as in Question no. 3*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 5

int IsEmpty(int *k)
{
    if((*k) <= 0)
        return 1;
    return 0;
}

int IsFull(int *k)
{
    if((*k) >= MAXLENGTH)
        return 1;
    return 0;
}

int Display(int circularQ[] , int *k, int *front , int *rear)
{
    if(IsEmpty(k))
    {
        printf("Empty circular queue []");
        return -1;
    }

    int CQitr = *front;
    for(int i = 0; i < *k; i++)
    {
        printf("%d ", circularQ[CQitr]);
        CQitr = CQitr % MAXLENGTH + 1;
    }
    printf("\n\n");

    return 0;
}

int Delete(int circularQ[] , int *k, int *front, int * rear)
{
    if(IsEmpty(k))
    {
        printf("Error: Queue Underflow\n");
        return -1;
    }

    int x = circularQ[*front + 1];
    *front = *front % MAXLENGTH + 1;
    (*k)--;

    return x;
}

int Add(int circularQ[], int x, int *k, int *front, int *rear)
{
    if(IsFull(k))
    {
        printf("Error: Circular Queue Overflow\n");
        return -1;
    }
    printf("Inside the Add\n");

    circularQ[*rear + 1] = x;
    *rear = *rear % MAXLENGTH + 1; 
    (*k)++;

    return 1;
}

int main()
{
    int k = 0, ch = 0, x, front, rear;
    printf("Enter the size of the circular queue: ");
    scanf("%d", &k);

    front = 0;

    int circularQ[MAXLENGTH];

    printf("Enter the circular queue: \n");
    for(int i = 0; i < k; i++)
        scanf("%d", &circularQ[i]);

    rear = k - 1;

    do{
        printf("\nSelect an operation:\n\
                Enter '1' to Add an element to the Circular Queue\n\
                Enter '2' to Delete an element from the Circular Queue\n\
                Enter '3' to Display the Circular Queue\n\
                Enter '4' to Quit\n\t==> ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                printf("\nEnter the element: ");
                scanf("%d", &x);

                if(Add(circularQ, x, &k, &front, &rear) == 1)
                {
                    printf("The queue after Add operation is: ");
                    Display(circularQ, &k, &front, &rear);
                }

                break;

            case 2:
                int x = Delete(circularQ, &k, &front, &rear) != -1;
                if(x)
                {
                    printf("The popped element is: %d\n", x);
                    printf("The Circular Queue after Delete operation is: ");
                    Display(circularQ, &k, &front, &rear);
                }

                break;
            
            case 3:
                printf("The Circular Queue is: ");
                Display(circularQ, &k, &front, &rear);
                break;

            default: break;
        }
    }while(ch != 4);

    printf("Exiting the Program\n");
    return 0;
}
