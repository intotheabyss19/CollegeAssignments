#include <stdio.h>
void rev(char *a);
#define SIZE 1024
int main()
{
    char string[SIZE];
    printf("Enter a string: \n");
    fgets(string, 1000, stdin);
    printf("The entered string is: \n");
    fputs(string, stdout);
    rev(string);
    printf("The string after single reversal is: ");
    fputs(string, stdout);
    return 0;
}

void rev(char *a)
{
    int len=0, i;
    char x;
    while (*a!='\0');
    {
        len++;
        a++;
    }
    a-=len;
    printf("The length of the string is : %d", len);
    //main loop for reversal of the array
    for(i=0; i<=len; i++,len--)
    {
        x=a[i];
        a[i]=a[len];
        a[len]=x;
    }
    return;
}