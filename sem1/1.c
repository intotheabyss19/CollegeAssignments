#include <stdio.h>

int add(int, int);

int main()
{
    int x, y, sum;
    printf("Enter first number:  ");
    scanf("%d", &x);
    printf("Enter second number: ");
    scanf("%d", &y);
    sum = add(x, y);
    printf("The sum is: %d\n", sum);
    printf("The sum is: %d", add(x, y));
    return 0;
}

int add(int n, int m)
{
    return n + m;
}