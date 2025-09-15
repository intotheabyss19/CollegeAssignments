/*
My first truly complicated project...
Python interpreter made by C compiler
*/

#include <stdio.h>

int type(char a[1024]);

int main()
{
    char line[1024];
    scanf("%s", &line[1024]);
    printf("%c", line[1024]);
    printf("%c", line[0]);
    return 0;
}

