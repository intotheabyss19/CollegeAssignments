/*
6. Write a program to store the elements of a two-dimensional array A2 in an array of structures S where each
element of the array of structures S is a structure object containing a one-dimensional array A1 that stores
one row of the two-dimensional array A2. To elaborate, the one-dimensional array A1 which is a member of
the structure object which is the ith element of the array of structures S will store the ith row of the two-
dimensional array A2. Take the elements of the two-dimensional array A2 as input from the user in row-
major order. Deciding the data type of A2 is left to the programmer’s discretion. Print the contents of the
array of structures S in a reader-friendly format as the final output of your program.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct structure{
    int *A;
} Struct;

void input(Struct *S, int r, int c)
{
    for(int i = 0; i < r; i++)
    {
        S[i].A = (int *)malloc(c * sizeof(int));
        for(int j = 0; j < c; j++)
            scanf("%d", &S[i].A[j]);
    }
}

void print(Struct *S, int r, int c)
{
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
            printf("%d ", S[i].A[j]);
        printf("\n");
    }
}

int main()
{   
    int r, c;
    printf("Enter the number of structure elements: ");
    scanf("%d", &r);
    Struct * S = calloc (r, sizeof(Struct));

    printf("Enter the size of each structure: ");
    scanf("%d", &c);
    printf("Enter elements: \n");
    input(S, r, c);
    printf("\n");
    print(S, r, c);

    //Free the allocated memory
    for(int i = 0; i < r; i++) {
        free(S[i].A);
    }
    free(S);

    return 0;

}
