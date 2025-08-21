/*9.
Write a program to delete the middle node of a doubly linked list, i.e. given a doubly linked list L of n
n
nodes, delete the ⌈ ⌉th node of L. Create a doubly linked list L of n nodes by taking n and the data items of
2
every node of L as input from the user. Display the nodes of L from head to tail before and after deleting the
middle node as shown in the sample final output given below.
Sample Final Output
Original linked list: 50 ↔ 40 ↔ 20 ↔ 15 ↔ 10
Modified linked list: 50 ↔ 40 ↔ 15 ↔ 10#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

void insertNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* lastNode = *head;
    while (lastNode->next) {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
    newNode->prev = lastNode;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        if (temp->next) {
            printf("↔ ");
        }
        temp = temp->next;
    }
    printf("\n");
}

void deleteMiddleNode(Node** head) {
    if (*head == NULL) {
        return;
    }
    int length = 0;
    Node* temp = *head;
    while (temp) {
        length++;
        temp = temp->next;
    }
    int middleIndex = (length + 1) / 2;
    if (middleIndex == 1) {
        *head = (*head)->next;
        if (*head) {
            (*head)->prev = NULL;
        }
        return;
    }
    temp = *head;
    for (int i = 1; i < middleIndex - 1; i++) {
        temp = temp->next;
    }
    Node* middleNode = temp->next;
    temp->next = middleNode->next;
    if (middleNode->next) {
        middleNode->next->prev = temp;
    }
    free(middleNode);
}

int main() {
    int n;
    printf("Enter the number of nodes: ");
   */