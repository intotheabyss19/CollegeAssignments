#include <stdio.h>

int main(int n)
{
    if (n > 10)
    {
        printf("\nEnd of the World");
        return 0;
    }
    n++;
    printf("Hello World\n\t");
    main(n);
    return 0;
};
