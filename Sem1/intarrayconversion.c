#include <stdio.h>
int main()
{
    int n, i = 0, j = 0, x,length, a[128];
    printf("Enter the integer: ");
    scanf("%d", &n);
    // program to send individual digits of the given number into an array
    while (n > 0)
    {
        a[i] = n % 10;
        n /= 10;
        i++;
    }
    printf("The length is %d\n", i);
    printf("The array before reversing is: \n");
    for(int j=0; j < i ; j++)
        printf("%d ", a[j]);
    length=i;
    printf("\n");
    // program to reverse the array:
    for (j=0,length; j <= length; j++, length--)
    {
        x = a[length];
        a[length]=a[j];
        a[j]=a[length];
    }
    printf("The array after reversing is: \n");
    for(int j=0; j < i ; j++)
        printf("%d ", a[j]);
    return 0;
}