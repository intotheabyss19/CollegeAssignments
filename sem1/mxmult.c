//Program to input and multiply two matrices
//by b230038
#include <stdio.h>

void multiply(int m1[][10],int m2[][10],int m3[][10],int r1,int c1,int r2, int c2);
void display(int m[][10],int r1,int c2);

int main()
{
    int a[10][10], b[10][10], c[10][10],row1,col1,row2,col2;
    printf("Enter the value of rows in matrix 1:\n\t==>");
    scanf("%d", &row1);
    printf("Enter the value of columns in matrix 1:\n\t==>");
    scanf("%d", &col1);
    printf("Enter the value of rows in matrix 2:\n\t==>");
    scanf("%d", &row2);
    printf("Enter the value of columns in matrix 2:\n\t==>");
    scanf("%d", &col2);
    if(col1==row2)
    {
        printf("\tFor Matrix 1:\n\n");
        for(int i=0; i<row1;i++)
        {   
            printf("Enter values for row %d:\n", i+1);
            for(int j=0;j<col1; j++)
            {
                printf("\tEnter value of element at %dth position:", j+1);
                scanf("%d", &a[i][j]);
            }
        }
        printf("Matrix 1 is\n");
        display(a,row1,col1);
        printf("\tFor Matrix 2:\n\n");
        for(int i=0; i<row2;i++)
        {   
            printf("Enter values for row %d:\n", i+1);
            for(int j=0;j<col2; j++)
            {
                printf("\tEnter value of element at %dth position:", j+1);
                scanf("%d", &b[i][j]);
            }
        }
        printf("Matrix 2 is\n");
        display(b,row2,col2);
        printf("\n\n");
        //final function call for multiplication
        printf("The output is:\n");
        multiply(a,b,c,row1,col1,row2,col2);
        display(c,row1,col2);
    }
    else
        printf("The provided matrix dimensions are not conformable for multiplication");
    return 0;
}


void multiply(int m1[][10],int m2[][10],int m3[][10],int r1,int c1,int r2, int c2)
{
    for(int i=0; i<r1; i++)
    {
        for(int j=0; j<c1; j++)
        {
            m3[i][j]=0;
            for(int k=0; k<=c2; k++)
            {
                m3[i][j]+=m1[i][k]*m2[k][j];
            }
        }
    }
}
void display(int m[][10],int r1,int c2)
{
    for(int i=0; i<r1; i++)
    {
        for(int j=0; j<c2; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}