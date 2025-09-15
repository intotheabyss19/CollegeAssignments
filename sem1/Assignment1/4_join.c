/*
4. Write a program to join two lists (of numbers) and store the resultant list in a third array with a function
called join. Call join from your main function to join two lists taken as input from the user, and then print
the resultant list, i.e. the third array containing the joined list, as the final output of your program. Define
join as follows: join(list1, list2, list3) will join list1 and list2, and then will store the result in list3. For
example, if list1 := <1, 2, 3, 4>, and list2 := <4, 5, 6, 7, 8>, then list3 will be < 1, 2, 3, 4, 4, 5, 6, 7, 8>.
*/

#include <stdio.h>

void join(int a[], int b[], int c[], int, int);
void create(int a[], int);

int main()
{
    int l1[100], l2[100], l3[200], i, n1, n2;
    printf("Enter the size of 1st array: ");
    scanf("%d", &n1);
    create(l1, n1); 
    printf("\nEnter the size of 2nd array: ");
    scanf("%d", &n2);
    create(l2, n2);
    join(l1,l2,l3, n1, n2);
    printf("\nThe resultant array is: ");
    for(i = 0 ; i < n1+n2; i++)
        printf("%d ", l3[i]);
    printf("\n");
    return 0;
}

void create(int a[],int n)
{
    for(int i = 0; i<n; i++)
    {
        printf("Enter the %dth element: ", i+1);
        scanf("%d", &a[i]);
    }
}

void join(int a[100], int b[100], int c[200], int n1, int n2)
{
    int i;
    for(i = 0; i<n1; i++ )
        c[i]=a[i];
    for(i; i<(n1+n2); i++)
        c[i]=b[i-n1];
}
