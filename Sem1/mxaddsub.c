cd //Program to input and add and subtract two matrices
//by b230038

#include <stdio.h>

void addsub(int m1[][10],int m2[][10],int m3[][10], int m4[][10],int r,int c);
void display(int m[][10],int r,int c);

int main()
{
    int a[10][10], b[10][10], c[10][10],d[10][10],row,col;
    printf("Enter the value of rows in matrix:\n\t==>");
    scanf("%d", &row);
    printf("Enter the value of columns in matrix:\n\t==>");
    scanf("%d", &col);
    printf("\tFor Matrix 1:\n\n");
    for(int i=0; i<row;i++)
    {   
        printf("Enter values for row %d:\n", i+1);
        for(int j=0;j<col; j++)
        {
            printf("\tEnter value of element at %dth position:", j+1);
            scanf("%d", &a[i][j]);
        }
    }
    printf("Matrix 1 is\n");
    display(a,row,col);
    printf("\tFor Matrix 2:\n\n");
    for(int i=0; i<row;i++)
    {   
        printf("Enter values for row %d:\n", i+1);
        for(int j=0;j<col; j++)
        {
            printf("\tEnter value of element at %dth position:", j+1);
            scanf("%d", &b[i][j]);
        }
    }
    printf("Matrix 2 is\n");
    display(b,row,col);
    printf("\n\n");
    addsub(a,b,c,d,row,col);
    printf("The output for addition is:\n");
    display(c,row,col);
    printf("The output for subtraction is:\n");
    display(d,row,col);
    return 0;
}


void addsub(int m1[][10],int m2[][10],int m3[][10],int m4[][10],int r,int c)
{
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            m3[i][j]=m1[i][j]+m2[i][j];
            m4[i][j]=m1[i][j]-m2[i][j];
        }
    }
}
void display(int m[][10],int r,int c)
{
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}