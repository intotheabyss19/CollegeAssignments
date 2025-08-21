#include <stdio.h>
int main()
{
    int n,i,j,k,temp;
    printf("Enter an integer: ");
    scanf("%d", &n);
    temp=n;
    // upper diagram
    for(i=0; i<n; i++)
    {
        for(j=0; j<i; j++)
            printf("*");
        for(j=0; j<temp*2; j++)
            printf(" ");
        temp-=1;
        for(j=0; j<i; j++)
            printf("*");
        printf("\n");
    }
    //middle portion
    for(i=0; i<n*2; i++)
        printf("*");
    printf("\n");
    temp=n;
    j=temp;
    //bottom part
    for (i=n-1; i>0; i--)
    {
        for(j=i; j>0 ; j--)
            printf("*");
        for(j; j<temp; j++)
            printf(" ");
        temp-=1;
        for(j=0; j<i; j++)
            printf("*");
        printf("\n");
    }
    return 0;
}