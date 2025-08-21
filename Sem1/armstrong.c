//takes upper limit in the main function, uses two separate functions to solve the problem

#include <stdio.h>

int armstrong(int);
int power(int, int);

int main()
{
    int n,i,flag;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("\"Armstrong\" numbers less than %d are:\n\t==>", n);
    for(i=1; i<=n; i++)     //loop to iterate all the way upto the upper limit
    {
        flag=armstrong(i);      //check if number is armstrong number
        if(flag==1)
            printf("%d ", i);       //if it is then print the number
    }
}

int armstrong(int n)
{
    int i=0, sum=0, pow=0, digit=0;
    for(i=n; i!=0; i/=10)       //calculate the length of the number first for the power
        pow++;
    for(i=n; i!=0; i/=10)       //run a loop for taking individual digits to the said power
    {
        digit = i%10;
        sum+=power(digit, pow);
    }
    if(sum==n)
        return 1;
    else
        return 0;
}

int power(int dig,int p)        //function for easily calculating the power to a given digit
{
    int prod=1, i=0;
    for(i=0; i<p; i++)
        prod*=dig;
    return prod;
}