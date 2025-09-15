/*
Write a function called findword which searches for a given string phrase in another string
paragraph. findword takes two strings, phrase and paragraph, as its arguments, and then returns
1 if phrase is found in paragraph, and returns 0 if phrase is not found in paragraph. In your main
function, take two strings p and q as input from the user, and then call findword and print whether
q is present in p. Produce your output according to the “Sample Output” given below.
*/

#include <stdio.h>
int findword(char para[1024],char str[64]);
int p;
int main()
{
    printf("%d", p);
    auto int flag;
    register int s=0;
    printf("%d", s);

    char para[1024], str[64];
    printf("Enter the paragraph: ");
    gets(para);
    printf("Enter the string: ");
    gets(str);
    flag = findword(para, str);
    switch(flag)
    {
        case 0:
            printf("The phrase '%s' was not found in the given paragraph", str);
            break;
        case 1:
            printf("The phrase '%s' was found in the given paragraph", str);
            break;
        default:
            break;
    }
    return 0;
}
    

int findword(char para[1024], char str[64])
{
    int i=0, j=0;
    while(para[i]!='\0')
    {
        if(para[i]==str[j])
            j++;
        else
            j=0;
        if (str[j]=='\0')
            return 1;
        i++;
    }
    return 0;
}