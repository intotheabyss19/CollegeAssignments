/*wacp to reverse the sequence of a sentence
eg. hello world --> world hello*/

#include <stdio.h>

// Function to reverse a string in-place
void reverseString(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    int start = 0;
    int end = length - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Function to reverse individual words in a string
void reverseWords(char *str) {
    int start = 0;
    int end = 0;

    while (str[end] != '\0') {
        if (str[end] == ' ' || str[end] == '\n') {
            reverseString(&str[start]);
            start = end + 1;
        }
        end++;
    }

    reverseString(&str[start]);
}

int main() {
    char inputString[1000];
    printf("Enter a string: ");
    fgets(inputString, sizeof(inputString), stdin);

    // Step 1: Reverse the entire string
    reverseString(inputString);

    // Step 2: Reverse individual words in the reversed string
    reverseWords(inputString);

    // Print the reversed sentence
    printf("Reversed sentence: %s\n", inputString);

    return 0;
}
