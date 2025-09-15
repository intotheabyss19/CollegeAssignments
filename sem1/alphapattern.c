#include <stdio.h>

void pattern(int);
int main()
{
    int n, i;
    printf("Enter the number of lines: ");
    scanf("%d", &n);
    pattern(n);
    return 0;
}
void pattern(int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
            printf("%c", j + 97);
        printf("\n");
    }
    return;
}