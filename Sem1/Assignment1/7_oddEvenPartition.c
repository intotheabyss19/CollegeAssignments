/*
7. Write a program to partition a given array of integers into two segments of odd numbers and even numbers
such that the first segment contains all the odd numbers and the last segment contains all the even numbers,
and each segment contains elements in the same relative order in which they were stored in the list initially,
without using a second array, with a function called partition. 
For example, if a given array list is <10, 14, 15, 20, 13, 17, 40, 25, 30, 50>, 
then partition will rearrange list so that list becomes <15, 13, 17, 25, 10, 14, 20, 40, 30, 50>. 
Print the original array and the modified array as the final output of your program.
*/

#include <stdio.h>

void partition(int a[100], int);
void LRshift(int a[100], int , int);

int main()
{
    int i, size, intarray[100];
    printf("Enter the number of elements: ");
    scanf("%d", &size);
    for(i = 0; i<size; i++)
    {
        printf("Element no. %d: ", i+1);
        scanf("%d", &intarray[i]);
    }
    printf("The array so inserted is: ");
    for(i = 0 ; i<size; i++)
        printf("%d ", intarray[i]);
    
    //calling the partition function
    partition(intarray, size);
    printf("\nThe modified array is: ");
    for(i = 0 ; i<size; i++)
        printf("%d ", intarray[i]);
    printf("\n");
    return 0;
}

void partition(int a[100], int s)
{
    int i ,j = 0, buffer;
    for(i = 0; i< s; i++)
    {
        if(a[i]%2!=0)
        {
            buffer=a[i];
            LRshift(a, j, i);
            a[j]=buffer;
            j++;
        }
    }
}

//r is the rightmost index till where shifting has to be done
//l is leftmost index from where shifting has to be started
void LRshift(int a[100],int l, int r)
{
    for (int i = r; i>l; i--)
        a[i]=a[i-1];
}

//success