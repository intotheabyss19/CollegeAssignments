/*

Write two functions called delete and search to perform the delete operation and the search operation on a given array respectively

->delete(list, p, ...) will delete an element from a given position p from a given array list.
 delete will be a void type function which will moddify the array passed as a parameter.

->search(list, k, ...) will search for the element k in a given array list.
 If k is found in list, then search will return i if list[i]=k; otherwise search will return-1

*/
#include <stdio.h>


void insert(int a[100], int, int, int *);
void delete(int a[100], int, int *);
void printarray(int a[100], int);

int search(int a[100], int, int );

int main()
{
    int size, ch, ele, pos, n, i, k, array[100];
    printf("Enter the size of the Array: ");
    scanf("%d", &size);
    for(i=0; i<size; i++)
    {
        printf("Enter the %dth element of the Array: ", i+1);
        scanf("%d", &array[i]);
    }

    while(1)
    {
        printf("\nEnter the operation you want to perform;\n\tEnter 1 for insert function\n\tEnter 2 for delete function\n\tEnter 3 for search function\n\tEnter 0 to Exit\n\t\t==> ");
        scanf("%d", &ch);
        getchar();
        switch(ch)
        {
            case 0:
                return 0;
            case 1:
                printf("\n\tInsert Function Initiated\n");
                printf("Enter the element to be inserted: ");
                scanf("%d", &ele);
                printf("Enter the position: ");
                scanf("%d", &pos);
                insert(array, ele, pos - 1, &size);
                printf("New size is %d", size);
                printf("\n\nOperation Performed Successfully.\n");
                printarray(array, size);
                break;
            case 2:
                printf("\n\tDelete Function Initiated\n");
                printf("Enter the position of element to be deleted: ");
                scanf("%d", &pos);
                delete(array, pos - 1, &size);
                printf("New size is %d", size);
                printf("\n\nOperation Performed Successfully.\n");
                printarray(array,size);
                break;
            case 3:
                printf("\n\tSearch Function Initiated\n");
                printf("Enter the element to be searched: ");
                scanf("%d", &ele);
                k = search(array, ele, size);
                if(k==-1)
                    printf("\nElement Not Found\n");
                else
                    printf("\nThe given element is present at position: %d\n", k);
                break;
            default:
                return 0;
        }
    }
    return 0;
}

void insert(int a[100], int e, int p, int *s)
{
    int i;
    for(i=(*s); i>p; i--)
        a[i]=a[i-1];
    a[p]=e;
    (*s)++;
}

void delete(int a[100], int p, int *s)
{
    int i;
    for(i=p; i < (*s) ; i++)
        a[i]=a[i+1];
    (*s)--;
}

int search(int a[100], int k, int s)
{
    int i;
    for(i = 0; i<s; i++)
    {
        if(a[i]==k)
            return i+1;
    }
    return -1;
}

void printarray(int a[100], int n)
{
    printf("\nThe modified array is: ");
    for(int i=0; i<n; i++)
        printf("%d", a[i]);
    printf("\n");
}

//success