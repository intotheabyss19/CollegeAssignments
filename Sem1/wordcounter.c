#include <stdio.h>
#define LEN 1000
int wordcounter(char *arr);
int main()
{
    int words;
    char str[LEN];
    printf("Enter the string: ");
    fgets(str, 500, stdin);
    words= wordcounter(str);
    printf("The number of words in the given string is: %d", words);
    return 0;
}

int wordcounter(char arr[50])
{
    int count=0;
    char *p;
    p=arr;
    while (*p != '\0')
    {
        if(*p == ' ' && *(p+1)!=' ')
            count++;
        p++;
    }
    return count;
}