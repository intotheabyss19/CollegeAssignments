/*
7. Write a program to search for a given number in an array by binary search with a function called
binary_search. Take an array A and a number k as input from the user, sort A with the function
selection_sort from Question no. 5, and then check whether k is present in A by calling binary_search
from the main function. Print the result of the search with an appropriate message as the final output of
your program.
*/

#include <stdio.h>
#include <stdlib.h>

#define SWAP(t, x, y) { t buffer; buffer = x; x = y; y = buffer;}

// Function to perform selection sort in ascending order
void selectionsort(int arr[], int n) 
{
    int i, j, max_index;
    int temp;

    for (i = 0; i < n - 1; i++) 
    {
        max_index = i;
        // Find the index of the maximum element in the unsorted part of the array
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[max_index])
                max_index = j;
        if(max_index != i)
            SWAP(int, arr[i], arr[max_index]);
    }
}

int binarysearch(int *arr, int n, int k) 
{
    int i;
    for()
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

    selectionsort(arr, n);

    int index = binarysearch(arr, n, k);

    if (index != -1)
        printf("The value %d was found at position %d.\n", k, index+1);
    else
        printf("The value %d was not found in the array.\n", k);

    return 0;
}
