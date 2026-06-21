/*
3. Write a program to find the product of two matrices. Take two matrices as input from the user in row-
major order, check whether the two matrices are compatible for multiplication, and then, if they are
compatible, multiply them and create the product matrix. Display the product matrix as the final output of
your program in row-major order. If the matrices are not compatible for multiplication, display an
appropriate message.
*/

#include <stdio.h>

void Multiplication(int A[100][100], int B[100][100], int C[100][100], int r1, int r2, int c1, int c2)
{
    int i, j, k, sum = 0;
    for(i = 0; i < r1; i++)
    {
        for(j = 0; j < c2; j++)
        {
            C[i][j] = 0;
            for(k = 0; k < c1; k++)
                C[i][j] += A[i][j] * B[j][i];
        }
    }
}

int main()
{
    int i, j, r1, c1, r2, c2, M1[100][100], M2[100][100], M3[100][100];
    printf("For Matrix 1:\n\tNumber of rows: ");
    scanf("%d", &r1);
    printf("\tNumber of columns: ");
    scanf("%d", &c1);

    printf("For Matrix 2:\n\tNumber of rows: ");
    scanf("%d", &r2);
    printf("\tNumber of columns: ");
    scanf("%d", &c2);

    if(c2 != r1)
    {
        printf("Matrices are not compatible for multiplication.\n");
        return 0;
    }

    printf("Enter Matrix 1\n");
    for(i = 0; i < r1; i++)
        for(j = 0; j < c1; j++)
            scanf("%d", &M1[i][j]);
    
    printf("Enter Matrix 2\n");
    for(i = 0; i < r2; i++)
        for(j = 0; j < c2; j++)
            scanf("%d", &M2[i][j]);

    Multiplication(M1, M2, M3, r1, c1, r2, c2);

    printf("\nThe Product Matrix is: \n");
    for(i = 0; i < r1; i++)
    {
        for(j = 0; j < c2; j++)
            printf("%d ", M3[i][j]);
        printf("\n");
    }
    return 0;
}
