#include <stdio.h>

void selection_sort(int *arrayptr, int size)
{
    int max;
    for(int i = 1; i < size; i++)
    {
        max = arrayptr[i-1];
        for(int j = i; j < size; j++)
        {
            if (max > arrayptr[j])
                max = arrayptr[j];
        }
        if(max != arrayptr[i])
        {
            //code for swapping max and arrayptr[i]
            max = max^arrayptr[i];
            arrayptr[i] = max^arrayptr[i];
            max = max^arrayptr[i];
        }
    }
}

int main()
{
    int i, n, array[100];
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    //loop to insert the elements
    for(i = 0; i < n; i++)
        scanf("%d", &array[i]);

    selection_sort(array, n);

    //printing the array
    for(i = 0; i < n; i++)
        printf("%d ", array[i]);
}