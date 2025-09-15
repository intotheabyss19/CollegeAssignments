#include <stdio.h>

int main()
{
    printf("Running test.c\n");
    int max = 5, j = 0;
    for(int i = 0 ; i < 15; i++)
    {
        printf("%d ", j);
        j = j % max + 1;
    }
    return 0;
}