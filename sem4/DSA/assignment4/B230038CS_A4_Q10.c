// B230038CS - Q10 - A4

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

Node* createList(int n) {
    Node* head = NULL;
    Node* tail = NULL;
    int data;

    for (int i = 0; i < n; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &data);

        Node* newNode = createNode(data);
        if (!newNode) return NULL;

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    return head;
}

void displayList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* temp = head;
    while (temp) {
        printf("%d", temp->data);
        if (temp->next) {
            printf(" ↔ ");
        }
        temp = temp->next;
    }
    printf("\n");
}

void deleteAlternateNodes(Node* head) {
    if (head == NULL) return;

    Node* current = head->next;
    Node* temp;

    while (current) {
        temp = current;
        if (current->prev) {
            current->prev->next = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        }
        current = current->next ? current->next->next : NULL;

        free(temp);
    }
}

int main() {
    int n;
    printf("Enter the number of nodes in the list: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("List must have at least one node.\n");
        return 1;
    }
    Node* head = createList(n);
    printf("Original list: ");
    displayList(head);

    deleteAlternateNodes(head);
    printf("Modified list: ");
    displayList(head);

    return 0;
}

