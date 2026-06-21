/*
2. Similar to Question no. 1 above, write a program to partition an array of integers into two subarrays of
prime numbers and composite numbers. Take the array as input from the user, rearrange its elements, and
display the modified array as the final output of your program. For example, the array {17, 14, 15, 7, 9, 31,
67, 89, 90, 19} will be partitioned and modified to {17, 7, 31, 67, 89, 19, 14, 15, 9, 90}
*/

#include <stdio.h>

int primecheck(int n)
{
    if (n == 1 || n == 0)
        return 0;
    for (int i = 2; i <= n / 2; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

void primePartition(int arr[], int n)
{
    int i, j, primei = 0;
    for(i = 0; i < n; i++)
    {
        if(primecheck(arr[i]))
        {
            if(arr[i] != primei)
            {
                int temp = arr[primei];
                arr[primei] = arr[i];
                arr[i] = temp;
            }
            primei++;
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

    primePartition(arr, n);
    printf("The array after partition is: ");
    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
