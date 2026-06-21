// B230038CS - Yash Gupta - Lab 3

/*
 * Prog 3. Assume a linked list as given in the following figure:
 * Write program with following methods
 * (a) A method to insert a new element after a given element in the linked
 * list. (b) A method to insert a new element at the end of the linked list. (c)
 * A method to print all the elements of the list.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  struct node *next;
  struct node *nnext;
} Node;

Node *newNode(int key) {
  Node *newnode = malloc(sizeof(Node));
  newnode->key = key;
  newnode->next = NULL;
  newnode->nnext = NULL;
  return newnode;
}

void printList(Node *head) {
  printf("\nPrinting the list:\n");
  for (Node *ii = head; ii; ii = ii->next) {
    printf("%d -> ", ii->key);
  }
  printf("⌧\n");
}

int insertAtPos(Node **head, Node *newnode, int pos) {
  if (*head == NULL) {
    if (pos == 0) {
      *head = newnode;
      return 0;
    } else {
      return -1;
    }
  }

  Node *currentNode = *head;
  Node *prevNode = NULL;
  int currentPos = 0;

  while (currentPos < pos && currentNode != NULL) {
    prevNode = currentNode;
    currentNode = currentNode->next;
    currentPos++;
  }

  if (currentNode == NULL) {
    return -1;
  }

  newnode->next = currentNode->next;
  currentNode->next = newnode;

  currentNode->nnext = newnode->next;
  if (newnode->next != NULL) {
    newnode->nnext = newnode->next->next;
  }
  if (prevNode != NULL) {
    prevNode->nnext = newnode;
  }

  return 0;
}

void insertAtEnd(Node **head, Node *newnode) {
  if (*head == NULL) {
    *head = newnode;
    return;
  }
  Node *currentNode = *head, *prevNode = NULL;

  while (currentNode->next != NULL) {
    prevNode = currentNode;
    currentNode = currentNode->next;
  }

  currentNode->next = newnode;
  if (prevNode != NULL) {
    prevNode->nnext = newnode;
  }
}

void createList(Node **head, int n) {
  for (int i = 0; i < n; i++) {
    int key;
    printf("Enter key: ");
    scanf("%d", &key);
    insertAtEnd(head, newNode(key));
  }
}

int main() {
  int n = 0, pos = 0, key;
  Node *head = NULL;
  printf("Enter n: ");
  scanf("%d", &n);
  createList(&head, n);
  printList(head);

  printf("Enter key for the new node: ");
  scanf("%d", &key);
  printf("Enter position to insert after: ");
  scanf("%d", &pos);

  if (insertAtPos(&head, newNode(key), pos - 1) == 0) {
    printf("Element successfully inserted\n");
  } else {
    printf("Error: Invalid position\n");
  }
  printList(head);
  return 0;
}
