/*
7.Write a program to store the elements of the Pascal’s triangle in a matrix such that the ith row of the matrix
stores the ith row of the Pascal’s triangle in the correct order. Print the matrix with appropriate spacing so
that the Pascal’s triangle is displayed in the conventional way that looks like an isosceles triangle. Take the
number of rows of the Pascal’s triangle as a command-line argument.
Sample Execution (for showing 5 rows of Pascal’s triangle)
$ ./pascal_triangle.out 5↲
          1
       1    1
     1   2   1
  1   3    3   1
1   4   6   4   1
*/
/*
[ 1 0 0 0 0 ]
[ 1 1 0 0 0 ]
[ 1 2 1 0 0 ]
[ 1 3 3 1 0 ]
[ 1 4 6 4 1 ] 
*/

#include <stdio.h>
#include <stdlib.h>

void pascal(int **, int);

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s <int>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int i, j, k;

    int **P = calloc(n , sizeof(int *));
    for(i = 0; i < n; i++)
        P[i] = calloc(n, sizeof(int));

    pascal(P, n);
    //Print the triangle
    printf("\rThe pascal's triangle for input %d is:\n", n);
    for(i = 0; i < n; i++)
    {
        for(k = 0; k < n - i; k++)
            printf(" ");
        for(j = 0; j < i+1; j++)
            printf("%d ", P[i][j]);
        printf("\n");
    }

    //Freeing up the allocated memory
    for(i = 0; i < n; i++)
        free(P[i]);
    free(P);
    return 0;
}

void pascal(int **P, int n)
{
    int i, j;
    P[0][0] = 1;
    for(i = 1; i < n; i++)
        for(j = 0; j <= i+1; j++)
        {
            P[i][j] = P[i-1][j-1] + P[i-1][j];
            printf(" ");
        }
}