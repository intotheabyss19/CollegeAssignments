/*
Write a program to sort an array of real numbers in descending order by selection sort with a function
called selection_sort. Take an array A as input from the user in your main function, call selection_sort
from the main function with A as an argument, and then print the sorted array in the main function as the
final output of your program.
*/

#include <stdio.h>

// Function to perform selection sort in descending order
void selection_sort(float arr[], int n) {
    int i, j, max_index;
    float temp;

    for (i = 0; i < n - 1; i++) {
        max_index = i;

        // Find the index of the maximum element in the unsorted part of the array
        for (j = i + 1; j < n; j++) {
            if (arr[j] > arr[max_index]) {
                max_index = j;
            }
        }

        // Swap the maximum element with the first element of the unsorted part
        if (max_index != i) {
            temp = arr[i];
            arr[i] = arr[max_index];
            arr[max_index] = temp;
        }
    }
}

int main() {
    int n, i;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    float arr[n];

    printf("Enter %d real numbers separated by spaces: ", n);
    for (i = 0; i < n; i++) {
        scanf("%f", &arr[i]);
    }

    selection_sort(arr, n);

    // Print the sorted array
    printf("Sorted array in descending order: ");
    for (i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");

    return 0;
}
