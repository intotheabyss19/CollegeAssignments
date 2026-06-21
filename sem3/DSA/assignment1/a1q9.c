/*
9. Write a program to take an array of integers as input from the user, and then calculate the sum of all the
odd numbers of the array using a recursive function called add_odds. There should be no iterative
statement in add_odds to calculate the required sum. Display the required sum as the final output of
your program.
*/

#include <stdio.h>
int add_odds(int arr[], int n, int *);
int add(int arr[], int n);
int main()
{
    int n, i, sumOdds = 0, *oddSum = 0, arr[100];
    printf("Enter the number of integers: ");
    scanf("%d", &n);
    printf("Enter the integers: ");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Entered array is: ");
    for(i = 1; i< n; i++)
    {
        printf("%d ", arr[i]);
    }
    sumOdds = add(arr, n);
    printf("\nThe sum of odd numbers is: %d\n", sumOdds);
}

int add(int arr[], int n)
{
    if(n==1)
    {
        if(arr[1]%2 != 0)
            arr[0]+=arr[1];
        else return arr[0];
    }

    if(arr[n]%2 != 0){
        n--;
        arr[0]+=add(arr, n);
    }
    n--;
    add(arr, n);
}