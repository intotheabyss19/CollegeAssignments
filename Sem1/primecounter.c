#include <stdio.h>
int primecheck(int);
int main()
{
    int i, n, list[100];
    int *p;
    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &list[i]);
    //loop to printout the entire list of elements
    printf("The entered array is: ");
    for (i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
    printf("Primes are: ");
    for (i = 0; i<n; i++)
    {
        if( primecheck(list[i]) == 1)
            printf("%d ", list[i]);
    }
    return 0;
}

int primecheck(int n)
{
    int i;
    if (n<2)
        return 0;
    for (i = 2; i<n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}