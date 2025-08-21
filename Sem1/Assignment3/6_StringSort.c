/*
6. Write a program to sort a string in alphabetical order by selection sort with a function called sort_string.
Take a string as input from the user in your main function, call sort_string from the main function with
the given string as the only argument, and print the sorted string in the main function as the final output of
your program. For example, if the user enters the string “mango”, then the output should be “agmno”.
*/

#include <stdio.h>

#define SWAP(t, x, y) { t buffer; buffer = x; x = y; y = buffer;}

void stringsort(char str[]) 
{
    int i, j;
    int max_index, temp;
    while(str[i+1] != '\0') 
    {
        max_index = i;
        j = i + 1;
        while(str[j] != '\0')
        {
            if (str[j] < str[max_index])
                max_index = j;
            j++;
        }
        if(max_index != i)
            SWAP(char, str[i], str[max_index]);
        i++;
    }
}

int main()
{
    int i;
    char s[100];

    printf("Enter a str: \n");
    fgets(s, 99, stdin);

    stringsort(s);

    printf("\nThe str after sorting is: ");
    
    fputs(s, stdout);

    printf("\n");

    return 0;
}
