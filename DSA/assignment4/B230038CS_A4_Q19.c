// B230038CS - Q19 - A4

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    char word[50];
    struct Node* next;
} Node;

Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int i = 0;
    while (word[i] != '\0' && i < 49) {
        newNode->word[i] = word[i];
        i++;
    }
    newNode->word[i] = '\0';
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, const char* word) {
    Node* newNode = createNode(word);
    if (!newNode) return;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int compareStrings(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;
        }
        i++;
    }
    return str1[i] == str2[i];
}

void deleteWord(Node** head, const char* word) {
    Node *temp = *head, *prev = NULL;

    while (temp != NULL) {
        if (compareStrings(temp->word, word)) {
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

void displayList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        printf("%s", temp->word);
        if (temp->next != NULL) {
            printf(" ");
        }
        temp = temp->next;
    }
    printf("\n");
}

int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("This program utilises command line arguments.\nUsage: %s word1 word2 word3 ...\n>", argv[0]);
        return -1;
    }

    char sentence[500], wordToDelete[50];
    Node* head = NULL;

    printf("Enter a sentence: ");
    int i = 0;
    for (int j = 1; j < argc; j++) {
        for (int k = 0; argv[j][k] != '\0'; k++) {
            sentence[i++] = argv[j][k];
            if (i >= 499) break;
        }
        if (i >= 499) break;
        sentence[i++] = ' ';
    }
    sentence[i] = '\0';


    i = 0;
    while (sentence[i] != '\0') {
        if (sentence[i] == '\n') {
            sentence[i] = '\0';
            break;
        }
        i++;
    }

    char currentWord[50];
    int wordIndex = 0;
    for (i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == ' ' || sentence[i] == '\0') {
            if (wordIndex > 0) {
                currentWord[wordIndex] = '\0';
                append(&head, currentWord);
                wordIndex = 0;
            }
        } else {
            currentWord[wordIndex++] = sentence[i];
        }
    }
    if (wordIndex > 0) {
        currentWord[wordIndex] = '\0';
        append(&head, currentWord);
    }

    printf("L: ");
    displayList(head);

    printf("Word to delete: ");
    fgets(wordToDelete, sizeof(wordToDelete), stdin);

    i = 0;
    while (wordToDelete[i] != '\0') {
        if (wordToDelete[i] == '\n') {
            wordToDelete[i] = '\0';
            break;
        }
        i++;
    }

    deleteWord(&head, wordToDelete);
    printf("L: ");
    displayList(head);

    return 0;
}
