/*
4. Write a program to sort an array of numbers in ascending order by bubblesort with a function called
bubblesort. Take an array A as input from the user in your main function, call bubblesort from the main
function with A as an argument, and then print the sorted array in the main function as the final output of
your program.
*/

#include <stdio.h>
#include <stdlib.h>

#define SWAP(t, x, y) { t buffer; buffer = x; x = y; y = buffer;}

void bubblesort(int *Array, int size)
{
    int i, j;
    for(i = 0; i < size - 1; i++)
        for(j = 1; j < size - i; j++)
            if(Array[j - 1]>Array[j])
                SWAP(int, Array[j - 1], Array[j]);
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

    bubblesort(A, size);

    printf("\nThe array after sorting is: ");
    for(i = 0; i < size; i++)
        printf("%d ", A[i]);

    printf("\n");

    return 0;
}

//Done