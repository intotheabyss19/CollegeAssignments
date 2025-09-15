/*
1. Write a program to partition an array of integers into two subarrays by rearranging its elements in such a
way that the first subarray contains odd numbers and the second subarray contains even numbers, without
using a second array, and without changing the relative ordering among the odd numbers and the relative
ordering among the even numbers. Take the numbers of the array as input from the user, rearrange the
numbers of the array to partition it, and then display the modified array as the final output of your program.
For example, the array {17, 14, 15, 10, 25, 40, 56, 46, 98, 77} will be partitioned and modified to {17, 15,
25, 77, 14, 10, 40, 56, 46, 98}.
*/

#include <stdio.h>

void oddEvenPartition(int arr[], int n)
{
    int i, j, oddi = 0;
    for(i = 0; i < n; i++)
    {
        if(arr[i]%2 != 0)
        {
            if(arr[i] != oddi)
            {
                int temp = arr[oddi];
                arr[oddi] = arr[i];
                arr[i] = temp;
            }
            oddi++;
        }
    }
}

int main()
{
    int n, i, arr[50];
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    oddEvenPartition(arr, n);
    printf("The array after partition is: ");
    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
