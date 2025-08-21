// A C Program that can do all sorts of operations on Matrices using different kinds of functions.

#include <stdio.h>
#include <stdlib.h>

// Function Declarations
void MatrixDisplay(int **, int, int);
void MatrixInput();
void BetterInput(int **, int, int, char *);

void MatrixAddition_Subtraction(int);
void MatrixMultiplication_by_Scalar();
void MatrixMultiplication_of_two_Matrices();
void MatrixTranspose();
void MatrixDeterminant();
int SubDeterminant(int **, int);

void main()
{
    int ch;
    printf("\n\tEnter 1 for Addition of two Matrices");
    printf("\n\tEnter 2 for Subtraction of two Matrices");
    printf("\n\tEnter 3 for Multiplying a Matrix by a Scalar");
    printf("\n\tEnter 4 for Multiplication of two Matrices");
    printf("\n\tEnter 5 to get Transpose of a Matrix");
    printf("\n\tEnter 5 to get Determinant of a Matrix");
    printf("\n\tEnter 0 to Exit ");
    printf("\n\t==>");

    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        MatrixAddition_Subtraction(1);
        break;
    case 2:
        MatrixAddition_Subtraction(2);
        break;
    case 3:
        printf("\nMultiplying a Matrix by a Scalar\n");
        MatrixMultiplication_by_Scalar();
    case 4:
        printf("\nMultiplying a Matrix by a Matrix\n");
        MatrixMultiplication_of_two_Matrices();
    case 5:
        printf("\nTranspose of the Matrix\n");
        MatrixTranspose();
    default:
        break;
    }
    return;
}

// Function Definitons

void MatrixDisplay(int **matrix, int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            printf("\t%d", matrix[i][j]);
        printf("\n");
    }
}

void MatrixInput()
{
    return;
}

void BetterInput(int **matrix, int row, int col, char *text)
{
    int i, j, k, l;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            system("clear");
            printf("\n%s:\n", text);
            for (k = 0; k < row; k++)
            {
                printf("\n\t");
                for (l = 0; l < col; l++)
                {
                    if (i == k && j == l)
                        printf(" _");
                    else
                        printf(" x");
                }
            }
            printf("\n\nEnter the element at the indicated place ==> ");
            scanf("%d", &matrix[i][j]);
        }
    }
}

void MatrixAddition_Subtraction(int choice_of_operation)
{
    int **matrixA, **matrixB, **matrixC, row, col, i, j;
    char *header_message = "Entering Data for Matrix A";
    printf("Enter the Number of Rows: ");
    scanf("%d", &row);
    getchar();
    printf("Enter the Number of Columns: ");
    scanf("%d", &col);

    // Allocating memory to the Required Matrices
    matrixA = (int **)malloc(row * sizeof(int *));
    for (i = 0; i < row; i++)
        matrixA[i] = (int *)malloc(col * sizeof(int));

    matrixB = (int **)malloc(row * sizeof(int *));
    for (i = 0; i < row; i++)
        matrixB[i] = (int *)malloc(col * sizeof(int));

    matrixC = (int **)malloc(row * sizeof(int *));
    for (i = 0; i < row; i++)
        matrixC[i] = (int *)malloc(col * sizeof(int));

    // Entering data to Matrix 1 and 2
    BetterInput(matrixA, row, col, header_message);
    header_message = "Entering Data for Matrix B";
    BetterInput(matrixB, row, col, header_message);

    system("clear");
    printf("\nMatrix 1 is: \n");
    MatrixDisplay(matrixA, row, col);
    printf("Matrix 2 is: \n");
    MatrixDisplay(matrixB, row, col);

    // Performing addition/subtraction over Matrix 1 and 2 and Storing the Result in Matrix 3
    switch (choice_of_operation)
    {
    case 1:
        for (i = 0; i < row; i++)
            for (j = 0; j < col; j++)
                matrixC[i][j] = matrixA[i][j] + matrixB[i][j];

        // Displaying the Final Matrix
        printf("\nSum of the two Matrices (A + B) is: \n C =");
        break;
    case 2:
        for (i = 0; i < row; i++)
            for (j = 0; j < col; j++)
                matrixC[i][j] = matrixA[i][j] - matrixB[i][j];

        // Displaying the Final Matrix
        printf("\nDifference of the two Matrices (A - B) is: \n C =");
    default:
        break;
    }
    MatrixDisplay(matrixC, row, col);

    // freeing up the memory
    free(matrixA);
    free(matrixB);
    free(matrixC);
}

void MatrixMultiplication_by_Scalar()
{
    int **matrixA, **matrixB, scalar, row, col, i, j;
    char *header_message = "Enter Data for the following Matrix";
    printf("Enter the Number of Rows: ");
    scanf("%d", &row);
    printf("Enter the Number of Columns: ");
    scanf("%d", &col);

    // Allocating memory to the Required Matrices
    matrixA = (int **)malloc(row * sizeof(int *));
    for (i = 0; i < row; i++)
        matrixA[i] = (int *)malloc(col * sizeof(int));

    matrixB = (int **)malloc(row * sizeof(int *));
    for (i = 0; i < row; i++)
        matrixB[i] = (int *)malloc(col * sizeof(int));

    // Input Matrix
    BetterInput(matrixA, row, col, header_message);
    system("clear");
    printf("The Entered Matrix is: \n");
    MatrixDisplay(matrixA, row, col);

    // Taking input for the reuqired Scalar
    printf("\nEnter the scalar value: ");
    scanf("%d", &scalar);

    // scalar Multiplication
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            matrixB[i][j] = matrixA[i][j] * scalar;

    // Displaying the resultant Matrix
    printf("The resultant is: \n");
    MatrixDisplay(matrixB, row, col);

    // Freeing up the Dynamic Variables
    free(matrixA);
    free(matrixB);
}

void MatrixMultiplication_of_two_Matrices()
{
    int **matrixA, **matrixB, **matrixC, rowA, colA, rowB, colB, i, j, k;
    char *header_message = "Entering Data for Matrix A";
    printf("Enter the Number of Rows of Matrix A: ");
    scanf("%d", &rowA);
    printf("Enter the Number of Columns of Matrix A: ");
    scanf("%d", &colA);
    printf("Enter the Number of Rows of Matrix B: ");
    scanf("%d", &rowB);
    printf("Enter the Number of Columns of Matrix B: ");
    scanf("%d", &colB);

    // checking for comformabiltiy of matrices under multiplication
    if (colA != rowB)
    {
        printf("Sorry, The dimensions of the Matrices entered are not comformable for Multiplication...\n");
        return;
    }

    // Allocating memory to the Required Matrices
    matrixA = (int **)malloc(rowA * sizeof(int *));
    for (i = 0; i < rowA; i++)
        matrixA[i] = (int *)malloc(colA * sizeof(int));

    matrixB = (int **)malloc(rowB * sizeof(int *));
    for (i = 0; i < rowB; i++)
        matrixB[i] = (int *)malloc(colB * sizeof(int));

    matrixC = (int **)malloc(rowA * sizeof(int *));
    for (i = 0; i < rowA; i++)
        matrixC[i] = (int *)malloc(colB * sizeof(int));

    // Entering data to Matrix 1 and 2
    BetterInput(matrixA, rowA, colA, header_message);
    header_message = "Entering Data for Matrix B";
    BetterInput(matrixB, rowB, colB, header_message);

    // Performing the Multiplication Operation
    for (i = 0; i < rowA; i++)
        for (j = 0; j < colB; j++)
        {
            matrixC[i][j] = 0;
            for (k = 0; k < colA; k++)
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
        }
    system("clear");
    printf("\nMatrix 1 is: \n");
    MatrixDisplay(matrixA, rowA, colA);
    printf("Matrix 2 is: \n");
    MatrixDisplay(matrixB, rowB, colB);
    printf("The resultant Matrix is: \n");
    MatrixDisplay(matrixC, rowA, colB);
}

void MatrixTranspose()
{
    int **matrixA, **matrixB, row, col, i, j;
    char *header_message = "Entering Data for Matrix A";
    printf("Enter the Number of Rows: ");
    scanf("%d", &row);
    printf("Enter the Number of Columns: ");
    scanf("%d", &col);

    // Allocating memory to the Required Matrices
    matrixA = (int **)malloc(row * sizeof(int *));
    for (i = 0; i < row; i++)
        matrixA[i] = (int *)malloc(col * sizeof(int));

    matrixB = (int **)malloc(col * sizeof(int *));
    for (i = 0; i < col; i++)
        matrixB[i] = (int *)malloc(row * sizeof(int));

    // Entering data to Matrix 1 and 2
    BetterInput(matrixA, row, col, header_message);

    // Transpose Operation
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            matrixB[j][i] = matrixA[i][j];

    // Displaying the result
    system("clear");
    printf("\nThe Entered Matrix is: \n");
    MatrixDisplay(matrixA, row, col);
    printf("It's Transpose is: \n");
    MatrixDisplay(matrixB, col, row);
}

// void MatrixDeterminant()
// {
//     int **matrix, row, col, **submatrix, subrow, i, j, det;
//     char *header_message = "Enter the required Data for the Matrix";
//     printf("Enter the Number of Rows: ");
//     scanf("%d", &row);
//     printf("Enter the Number of Columns: ");
//     scanf("%d", &col);

//     if (row != col)
//     {
//         printf("Determinant is only possible for Square Matrices.");
//         return;
//     }

//     // Allocating memory to the Required Matrices
//     matrix = (int **)malloc(row * sizeof(int *));
//     for (i = 0; i < row; i++)
//         matrix[i] = (int *)malloc(row * sizeof(int));

//     SubDeterminant(submatrix, subrow);
// }

// int SubDeterminant(int **submatrix, int subrow)
// {
//     int i;
//     if (subrow < 2)
//         return (submatrix[0][1] * submatrix[1][0]) - (submatrix[1][0] * submatrix[0][1]);
//     else
//     {
//         for (i = 0; i < 4; i)
//             submatrix =
//     }
// }