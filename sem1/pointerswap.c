#include <stdio.h>
#define pf printf
#define SIZE 100
void swap(int *, int *);
int main()
{
    int x, y, arr[SIZE];
    pf("Enter the value of x: ");
    scanf("%d", &x);
    printf("Enter the value of y: ");
    scanf("%d", &y);
    printf("\nThe value of x is: %d\nThe value of y is: %d\n", x, y);
    printf("\nCalling the swap function...\n");
    swap(&x, &y);
    printf("\nThe value of x is: %d\nThe value of y is: %d\n", x, y);
    return 0;
}

void swap(int *p, int *q)
{
    int r;
    r = *p;
    *p = *q;
    *q = r;
    return;
}