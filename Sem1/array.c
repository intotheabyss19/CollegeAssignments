//program to display sum of 2nd, middle, 2nd last elements of an array
//by b230038


#include <stdio.h>
int main()
{
    int arr[100],n,l2,m,last, sum;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    for(int i=0; i<n;i++)
    {
        scanf("%d", &arr[i]);
    }
    l2=arr[1];
    if(n%2==0)
        m=n/2;
    else
        m=(n+1)/2;
    last=arr[n-2];
    sum = l2+m+last;
    printf("The sum of second, middle and second last element is %d",sum);
    return 0;
}