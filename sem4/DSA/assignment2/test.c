#include <stdio.h>

#define SWAP(a,b){a=a^b;b=a^b;a=a^b;}

int main()
{
    // int a = 5, b = 10;
    // printf("%d %d", a, b);
    // SWAP(a,b);
    // printf("%d %d", a, b);

    int a[5];
    for(int i = 0; i < 5; i++)
        printf("a[%d] is %d\n", i, a[i]);
    // printf(a[5]);
    return 0;
}

