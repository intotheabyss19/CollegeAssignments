/*
Write a program to search for a given value in a single-dimensional array by linear search with a function
called linear_search. linear_search will take an array A and a value k as parameters, and then will return
the index i if A[i] = k, otherwise will return -1 if k is not present in A. Take the elements of A and the value
of k as input from the user in your main function, and then call linear_search from the main function with
A and k as arguments. Print your final output with an appropriate message.
*/

#include <stdio.h>
#include <stdlib.h>

// Function to perform linear search
int linear_search(int *arr, int n, int k) 
{
    for (int i = 0; i < n; i++) 
    {
        if (arr[i] == k)
            return i;  
    }
    return -1;  
}

int main() 
{
    int n, k;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *arr=calloc(n, sizeof(int));

    printf("Enter the elements of the array separated by spaces: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the value to search for: ");
    scanf("%d", &k);

    int index = linear_search(arr, n, k);

    if (index != -1)
        printf("The value %d was found at position %d.\n", k, index+1);
    else
        printf("The value %d was not found in the array.\n", k);

    return 0;
}

//Done