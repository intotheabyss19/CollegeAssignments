#include <stdio.h>

void pattern(int);

int main()
{
    int n;
    printf("Enter the number of rows: ");
    scanf("%d", &n);
    pattern(n);
    return 0 ;
}

void pattern(int n )
{
    int i , j , k;
    for(i = 0 ; i < (n+1)/2 ; i++)
    {
        for(j = 0 ; j < i; j++)
            printf("*");
        for(k = n ; k > i*2 ; k--)
            printf(" ");
        for(j = 0; j < i ; j++)
            printf("*");
        printf("\n");
    }
    for(i = n ; i; i--)
        printf("*");
    printf("\n");
    for(i = 0 ; i < (n-1)/2 ; i++)
    {
        for(k = (n-1)/2 ; k > i ; k--)
            printf("*");
        for(j = 0; j <= i*2 ; j++)
            printf(" ");
        for(k = (n-1)/2 ; k >i ; k--)
            printf("*");
        printf("\n");
    }
}