/*
Write a function called substring which finds out the substring of a given string, according to the
definition given below. Take a string str, and two natural numbers i and k, as input from the user
using fgets in your main function, and then by calling substring from your main function print a
substring of str starting from ith position of str and of length k.
*/

#include<stdio.h>
void substring(char str[1024], char substr[512], int i, int k);
int main()
{
    char str[1024], substr[512];
    int start , length;
    printf("Enter a string: ");
    fgets(str, 1020, stdin);
    printf("Starting index of the substring?\n==>");
    scanf("%d", &start);
    printf("Length of the substring?\n==>");
    scanf("%d", &length);
    substring(str, substr, start , length );
    printf("Substring: ");
    fputs(substr, stdout);    
    return 0;
}

void substring(char str[1024], char substr[512], int i, int k)
{
    int j, l;
    for(j=i,l=0; j<=i+k; j++, l++)
        substr[l]=str[j];
    return;
}