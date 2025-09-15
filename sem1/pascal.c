/*
    Print a pascal's triangle 
    ^^^^^^^^^^^^1                       12
    ^^^^^^^^^^1 2 1                     10
    ^^^^^^^^^1 3 3 1                    09
    ^^^^^^^^1 4 6 4 1                   08
    ^^^^^^^1 5 10 10 5 1                07
    ^^^^^^1 6 15 20 15 6 1              06
    ^^^^^1 7 21 35 35 21 7 1            05
    ^^^^1 8 28 56 70 56 28 8 1          04
*/


#include <stdio.h>

void pascal(int n);

int main()
{
    int n;
    printf("Enter the number of lines: ");
    scanf("%d", &n);
    
    pascal(n);
    
    return 0;
}

void pascal(int n)
{
    int i, j, num;
    
    for (i = 0; i < n; i++)
    {
        for (int space = 0; space < n - i - 1; space++)
            printf("  ");
        
        num = 1;

        for (j = 0; j <= i; j++)
        {
            printf("%4d", num);
            num = num * (i - j) / (j + 1);
        }

        printf("\n");
    }
}
