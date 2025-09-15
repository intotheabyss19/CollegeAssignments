/*
5. Write a program to find out the minimum element and the maximum element of a given array, taken as
input from the user, with two functions called min and max, respectively. Call min and max from your
main function and print the results of min and max with appropriate output messages. Define the two said
functions as follows: min(list) returns the smallest element of the array list, and max(list) returns the
largest element of the array list.
*/

#include <stdio.h>

int min(int a[], int);
int max(int a[], int);

int main()
{
    int i,n, arr[100];
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    for(i = 0; i< n; i++)
    {
        printf("Enter the %dth element: ", i);
        scanf("%d", &arr[i]);
    }
    printf("The smallest element is: %d\n", min(arr,n));
    printf("The largest element is: %d\n", max(arr,n));
    return 0;
}

int min(int a[], int n)
{
    int i, mini=a[0];
    for(i=0; i<n; i++)
    {
        if(a[i]<mini)
            mini=a[i];
    }
    return mini;
}

int max(int a[], int n)
{
    int i, maxi=a[0];
    for(i=0; i<n; i++)
    {
        if(a[i]>maxi)
            maxi=a[i];
    }
    return maxi;
}

//success