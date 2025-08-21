#include <stdio.h>

// void pattern(int);
void pattern_arsh(int);
int main()
{
    int n, i=9;
    printf("Enter the number of lines: ");
    scanf("%d", &n);
    pattern_arsh(n);
    return 0;
}
// void pattern(int n)
// {
//     int i, j;
//     for (i = 0; i < n; i++)
//     {
//         for (j = i; j < n; j++)
//             printf("%c", j + 97);
//         printf("\n");
//     }
//     return 0;
// }

void pattern_arsh(int n)
{
    int i, j;
    for(i='a'; i<='a'+7; i++)
    {
        for( j=i; j<='a'+7; j++)
            printf("%c", j);
    printf("\n");
    }
}
