#include <stdio.h>
int kmn(int);
int fact(int);
int main()
{
    int km, check;
    printf("Enter an integer: ");
    scanf("%d", &km);
    check= kmn(km);
    if (check == 1)
        printf("The given number is a krishnamurthy number.");
    else
        printf("The given number is not a krishnamurthy number");
    return 0;
}

int kmn(int n)
{
    int sum = 0, dig;
    for(int i=n; i!=0 ; i/=10)
    {
        dig = i % 10;
        sum+=fact(dig);
    }
    if (sum == n)
        return 1;
    else
        return 0;
}

int fact(int n)
{
    if(n == 1)
        return 1;
    return n*fact(n-1);
}
