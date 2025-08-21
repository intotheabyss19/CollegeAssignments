#include <stdio.h>

void my_strcat(char str1[], char str2[]);

int main()
{
    char str1[] = "Hello";
    char str2[] = "World";
    my_strcat(str1, str2);
    printf("%s", str1);
}

void my_strcat(char str1[], char str2[])
{
    char *i, *j;

    for (i = str1; *i != '\0'; i++);  // i gets the address of the last element.
    for (j = str2; *j != '\0'; j++, i++)
        *i = *j;
    *i = '\0';
    
}