/*
5. Write a program to store a matrix of names and then print the names contained in the principal diagonal of
the matrix. Take the dimensions of the matrix as input from the user, store names in the matrix (where the
matrix is implemented with a three-dimensional character array) in row-major order so that each element
of the matrix is a name, and then display the list of names contained in the principal diagonal of the matrix,
in the correct order from the top left element to the bottom right element of the principal diagonal, as the
final output of your program.
*/


#include <stdio.h>
#define NameLength 100
#define MaxRows 100
#define MaxColumns 100

void PrincipalNames(char N[100][100][100], int d1, int d2)
{
    int i, j;
    printf("Principal Names are: \n");
    for(i = 0, j = 0; i < d1 && j < d2; i++, j++)
        printf("%s\n", N[i][j]);
}

int main()
{
    int d1, d2, d3, i, j, k;
    char Names[MaxRows][MaxColumns][NameLength];
    printf("Rows: ");
    scanf("%d", &d1);
    printf("Columns: ");
    scanf("%d", &d2);
    printf("Max Name Length: ");
    scanf("%d", &d3);

    printf("Enter the Matrix: \n");

    for(i = 0; i < d1; i++)
        for(j = 0; j < d2; j++)
            scanf("%s", &Names[i][j]);

    PrincipalNames(Names, d1, d2);
    return 0;
}
