/*wacp to check whether a given string is a palindrome. constraint: do not use a second array in your program*/
#include <stdio.h>
int main()
{
    char str[64];
    int palindrome=1,i=0,j=0;
    printf("Enter the string:\n==>");
    fgets(str,32,stdin);
    while(str[i]!='\0')
        i++;
    i--;
    i--;
    for(i,j;i>=j;i--,j++)
    {
        if(str[i]!=str[j])
        {
            palindrome=0;
            break;
        }
    }
    printf("The given string ");
    if(palindrome==1)
        printf("is a palindrome");
    else
        printf("is not a palindrome");
    return 0;
}