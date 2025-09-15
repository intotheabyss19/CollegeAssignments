/*wacp to concatenate two strings.
take two strings as input, and then concatenate the two strings and store the resultant string in a third variable, displayy the resultant string
take third string as variable*/

#include <stdio.h>
int main()
{
    char c1[64], c2[64], c12[128];
    int i=0,j=0;
    printf("Input string 1: ");
    fgets(c1, 32, stdin);
    printf("Input string 2: ");
    fgets(c2, 32, stdin);
    while (c1[i] != '\0')
    {
        c12[i] = c1[i];
        i++;
    }
    i--;
    while(c2[j]!='\0')
    {
        c12[i+j]=c2[j];
        j++;
    }
    printf("The concatenated string is: ");
    fputs(c12, stdout);
    return 0;
}