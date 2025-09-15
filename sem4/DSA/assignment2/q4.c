/*. 
Write a program to find the sum of the elements of the principal diagonal of a matrix. Take a matrix of real
numbers as input from the user in row-major order, and then print the sum of the principal diagonal
elements of the matrix as the final output of your program. Also, print the elements of the principal
diagonal of the matrix.
*/

#include <stdio.h>

int sumOfDiagonals(int A[100][100], int r, int c)
{
    int i, j, sum = 0;
    for(i = 0, j = 0; i < r && j < c; i++, j++)
        sum += A[i][j];

    return sum;
}

int main()
{
    int r, c, M[100][100];
    printf("Number of rows: ");
    scanf("%d", &r);
    printf("Number of columns: ");
    scanf("%d", &c);

    printf("Enter the Matrix: \n");

    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            scanf("%d", &M[i][j]);

    printf("The sum of elements of the principal diagonal of following matrix is %d\n", sumOfDiagonals(M, r, c));
    return 0;
}
