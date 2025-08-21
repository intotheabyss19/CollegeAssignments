/*
7. Write a program to enter a matrix from the user where each element of the matrix is an integer, and then
print the sum of all elements of the matrix.
*/

#include <stdio.h>

int main()
{
    int r, c, i, j, sum = 0, matrix[100][100];
    printf("Enter the number of rows: ");
    scanf("%d", &r);
    printf("Enter the number of columns: ");
    scanf("%d", &c);
    
    for(i = 0; i < r; i++)
        for(j = 0; j < c; j++)
            scanf("%d", &matrix[i][j]);

    printf("Sum of all elements is: ");
    for(i = 0; i < r; i++)
        for(j = 0; j < c; j++)
            sum += matrix[i][j];

    printf("%d\n", sum);
    return 0;
}

//Finished