/*
1.Write a program to implement the following operations on a given array list (of any data type) of size k,
where list and k are taken as input from the user. Each operation should be implemented by a function
according to the definition of the operation given below. After initially taking list and k as input from the
user, the user will be shown a menu-based interface where the user will choose to execute an operation.
The menu will be repeatedly displayed until the user chooses to quit. Do not use any external variable.
Insert(list, x, p, k) := Inserts element x in array list at position p and updates size k of list.
Delete(list, p, k) := Delete element x from position p of array list, updates size k of list, and returns x.
Empty(list, k) := Deletes all elements of array list and updates size k of list.
Display(list, k) := Display array list of size k in the correct order (from beginning to end).
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 100

int Display(int list[] , int *k)
{
    if((*k) < 0)
    {
        printf("Empty list []");
        return -1;
    }

    for(int i = 0; i < *k; i++)
        printf("%d ", list[i]);
    printf("\n\n");

    return 0;
}

int Delete(int list[] , int p, int *k)
{
    if(*k <= 0)
    {
        printf("Error: List is already empty\n");
        return -1; 
    }
    
    if(p <= 0 || p > *k)
    {
        printf("Error: Invalid value of p");
        return -1;
    }

    for(int i = p; i < *k; i++)
        list[i] = list[i+1];
    
    (*k)--;
    return 1;
}

void Empty(int list[], int *k)
{
    (*k) = -1;
}

int Insert(int list[], int x, int p, int *k)
{
    if((*k >= 1 )? p > *k : 0 || p < 0)
    {
        printf("Error: Invalid position number\n");
        return -1;
    }
    for(int i = *k; i >= p; i--)
        list[i+1] = list[i];

    list[p] = x;
    (*k)++;

    return 1;
}


int main()
{
    int k = -1, ch = 0, x, p;
    printf("Enter the size of the list: ");
    scanf("%d", &k);

    int list[MAXLENGTH];

    printf("Enter the list: \n");
    for(int i = 0; i < k; i++)
        scanf("%d", &list[i]);
    
    do{
        printf("\nSelect an operation: (Enter '0' to Exit)\n\
                Enter '1' to insert an element to the list\n\
                Enter '2' to delete an element from the list\n\
                Enter '3' to Empty the list\n\
                Enter '4' to Display the entire list\n\t==> ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 0:
                break;
            
            case 1:
                printf("\nEnter the element: ");
                scanf("%d", &x);

                printf("Enter the position 'p': ");
                scanf("%d", &p);

                if(Insert(list, x, p - 1, &k) == 1)
                {
                    printf("The List after insertion operation is: ");
                    Display(list, &k);
                }

                break;
            
            case 2:
                printf("\nEnter the position of element to be deleted: ");
                scanf("%d", &p);

                if(Delete(list, p - 1, &k) == 1)
                {
                    printf("The List after deletion operation is: ");
                    Display(list, &k);
                }

                break;
            
            case 3:
                Empty(list, &k);
                printf("The list is now empty: ");
                Display(list, &k);
                break;
            
            case 4:
                printf("The list is: ");
                Display(list, &k);
                break;

            default: break;
        }
    }while(ch);

    printf("Exiting the Program\n");
    return 0;
}
