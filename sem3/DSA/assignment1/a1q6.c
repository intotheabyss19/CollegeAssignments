/*
6. Write a program to take an array of strings as input from the user, and then modify the array such that
all the strings in the array are reversed, without using any second array, i.e. you may use only one two-
dimensional array in your program. Display the modified array of strings as the final output of your
program. Reversing the string means to rearrange the characters of a string in the reverse order
compared to the original string, i.e. reversing the string “computer” gives the resultant string as
“retupmoc”.
*/

#include <stdio.h>

int main()
{
    char str[100][100];
    int i;

    for (i = 0; scanf("%s", str[i]) == 1; i++) {
        // Check if the input is an empty string
        if (str[i][0] == '\0') {
            break;
        }
    }

    printf("i is %d\n", i);
    return 0;
}

// void revstring(char str[][])
// {
//     for(int )
// }