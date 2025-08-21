#include <stdio.h>
#define MAXLINE 1024

int main()
{
    int i, j;
    char str[MAXLINE];
    printf("Enter a string: ");
    fgets(str, MAXLINE, stdin);

    // for (i = j = 0; str[i] != '\n'; i++) {
    //     if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
    //         continue;
    //     str[j] = str[i];
    //     j++;
    // }
    // str[j] = '\0';

    printf("%s\n", str);

    return 0;
}       