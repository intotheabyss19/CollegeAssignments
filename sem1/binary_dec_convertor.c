#include <stdio.h>
int decimal_to_binary(int);
int binary_to_decimal(int);
int main()
{
    int ch,n;
    while(1)
    {
        printf("Enter 0 to convert a decimal number to binary,\nEnter 1 to convert a binary number to decimal\n Enter anything else to exit:\n==> ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 0:
                printf("Enter a decimal number: ");
                scanf("%d", &n);
                printf("The binary conversion for the given decimal number is: %d\n\n", decimal_to_binary(n));
                break;
            case 1:
                printf("Enter a binary number: ");
                scanf("%d", &n);
                printf("The decimal conversion for the given binary number is: %d\n\n", binary_to_decimal(n));
                break;
            default:
                 return 0;
        }
    }
    return 0;
}

int decimal_to_binary(int dec)
{
    int bin=0, i;
    for(i=1; dec!=0; i*=10)
    {
        bin += (dec % 2) *i ;
        dec/=2;
    }
    return bin;
}

int binary_to_decimal(int bin)
{
    int dec=0, i;
    for(i=1; bin; i*=2)
    {
        dec+=i*(bin%10);
        bin/=10;
    }
    
    return dec;
}