#include <stdio.h>
void f1()
{
    int list[]= {10,20,30,40,50,60,70}, i, *j;
    for(i=0, j=list; i<7; ++*j, ++j , i+=2);
    for(j=list, i=0; i<7; i++)
        printf("%d, ", *(j+i));
}

int main()
{
    // int i;
    // i = getchar();
    printf("%d", EOF);
    return 0;
}