/*
5. Write a program to sort an array of real numbers in descending order by selection sort with a function
called selection_sort. Take an array A as input from the user in your main function, call selection_sort
from the main function with A as an argument, and then print the sorted array in the main function as the
final output of your program.
*/

#include <stdio.h>
#include <stdlib.h>

#define SWAP(t, x, y) { t buffer; buffer = x; x = y; y = buffer;}

// Function to perform selection sort in descending order
void selectionsort(int arr[], int n) 
{
    int i, j, max_index;
    int temp;

    for (i = 0; i < n - 1; i++) 
    {
        max_index = i;
        // Find the index of the maximum element in the unsorted part of the array
        for (j = i + 1; j < n; j++)
            if (arr[j] > arr[max_index])
                max_index = j;
        if(max_index != i)
            SWAP(int, arr[i], arr[max_index]);
    }
}

int main()
{
    int i, size;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int *A = calloc (size , sizeof(int));

    printf("Enter the elements of the array separated by spaces: ");
    for(i = 0; i < size; i++)
        scanf("%d", &A[i]);
    printf("\n");

    selectionsort(A, size);

    printf("\nThe array after sorting is: ");
    for(i = 0; i < size; i++)
        printf("%d ", A[i]);

    printf("\n");

    return 0;
}

