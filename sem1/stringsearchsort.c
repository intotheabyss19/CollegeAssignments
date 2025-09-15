#include <stdio.h>
#include <string.h>

#define pf printf

int main()
{
    char str[256];
    char search[32];
    char wordlist[64][64];
    char revstr[256];
    int i = 0, j = 0, k = 0, x = 0, wordno = 1, len = strlen(str), wlen;
    pf("Enter the string: ");
    fgets(str, 255, stdin);
    pf("Enter the substring to be searched: ");
    fgets(search, 255, stdin);

    // loop for performing the search operation
    while (str[i] != '\0')
    {
        while (search[j] == str[i])
        {
            if (search[j] == str[i])
                j++;
            else
                j = 0;

            if (search[j + 1] == '\0')
            {
                printf("The given search substring occurs at position %d\n", i + 2 - strlen(search));
                j = 0;
            }
        }
        i++;
    }

    // loop for creating the wordlist
    printf("loop1");
    for (i = 0; i < len; i++)
    {
        if (str[i] != ' ')
        {
            wordno++;
            j = 0;
            k = 0;
        }
        wordlist[wordno - 1][j] = str[i];
    }
    // loop for sorting alphabetically
    printf("loop2");
    while (1)
    {
        for (j = 0; j < wordno; j++)
        {
            x = 0;
        }
    }

    puts(revstr);
    return 0;
}