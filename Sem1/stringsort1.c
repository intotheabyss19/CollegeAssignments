/*
WACP that reads and sorts the individual word of a given string alphabetically
*/

#include<stdio.h>
// Function to determine if a character is a space or a newline
int isSpaceOrNewline(char c) {
    return c == ' ' || c == '\n';
}

// Function to compare two strings for sorting
int compareStrings(const char *a, const char *b) {
    while (*a && *b) {
        if (*a < *b) {
            return -1;
        } else if (*a > *b) {
            return 1;
        }
        a++;
        b++;
    }
    if (*a) {
        return 1;
    } else if (*b) {
        return -1;
    }
    return 0;
}

// Function to swap two strings
void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    char inputString[1000];
    printf("Enter a string: ");
    fgets(inputString, sizeof(inputString), stdin);

    // Sort the individual words alphabetically
    char *words[100]; // Assuming a maximum of 100 words
    int wordCount = 0;
    char *start = inputString;

    while (*start) {
        while (isSpaceOrNewline(*start)) {
            start++;
        }
        if (*start == '\0') {
            break;
        }

        char *end = start;
        while (*end && !isSpaceOrNewline(*end)) {
            end++;
        }

        words[wordCount] = start;
        wordCount++;
        start = end;
        if (*start) {
            *start = '\0'; // Null-terminate the word
            start++;
        }
    }

    // Bubble sort to sort the words
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = 0; j < wordCount - i - 1; j++) {
            if (compareStrings(words[j], words[j + 1]) > 0) {
                swap(&words[j], &words[j + 1]);
            }
        }
    }

    // Print the sorted words in the same string
    printf("Sorted words in the string:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s", words[i]);
        if (i < wordCount - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}
