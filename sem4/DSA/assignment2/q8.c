/*
8. Write a function called add_to_sortedlist which takes a sorted array of numbers called list and a number
num as its arguments, and then inserts num at the correct position in list so that list remains sorted. In your
main function, take a set of n random numbers as input from the user, and then call add_to_sortedlist for
n times to store the numbers in an array A so that A always remains sorted. Print A in the correct order as
the final output of your program. Do not use any second array.
*/

#include <stdio.h>
#include <stdlib.h>

void add_to_sortedlist(int list[], int num, int *n ) 
{
    int i;
    for (i = *n - 1; (i >= 0 && list[i] > num); i--) {
        list[i + 1] = list[i];  // Shift elements to the right to make room for num
    }
    // Insert the number at the correct position
    list[i + 1] = num;
    (*n)++;  // Increase the size of the array
}

int main()
{
    int n, i, key;
    printf("Enter the size of the list: ");
    scanf("%d", &n);

    int *list = calloc(n, sizeof(int));

    printf("Enter the numbers: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &key);
        add_to_sortedlist(list, key, i+1);
    }

    printf("Printing the sorted list: ");
    for(i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
    // freeing up space
    free(list);

    return 0;
}