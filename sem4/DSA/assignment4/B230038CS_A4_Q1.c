// B230038CS - Q1 - A4
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node {
  int key;
  struct node *next;
} Num;

void display(Num *head) {
  Num *ii = head;
  printf("Linked List:");
  while (ii != NULL) {
    printf(" -> %d", ii->key);
    ii = ii->next;
  }
  printf("\n");
}

void displayOdd(Num *head) {
  Num *ii = head;
  printf("Odd Values:");
  while (ii != NULL) {
    if (ii->key % 2 != 0)
      printf(" -> %d", ii->key);
    ii = ii->next;
  }
  printf("\n");
}

void displayEven(Num *head) {
  Num *ii = head;
  printf("Even Values:");
  while (ii != NULL) {
    if (ii->key % 2 == 0)
      printf(" -> %d", ii->key);
    ii = ii->next;
  }
  printf("\n");
}

int main() {
  Num *head = NULL;
  Num *tail = NULL;
  int n, i;

  printf("Enter the number of items: ");
  scanf("%d", &n);

  if (n > SIZE) {
    printf("Cannot enter more than %d items.\n", SIZE);
    return 1;
  }

  printf("Enter the items: ");
  for (i = 0; i < n; i++) {
    Num *newNode = malloc(sizeof(Num));
    if (newNode == NULL) {
      printf("Memory allocation failed!\n");
      return 1;
    }
    scanf("%d", &newNode->key);
    newNode->next = NULL;

    // Link the new node to the list
    if (head == NULL) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
  }

  display(head);
  displayOdd(head);
  displayEven(head);

  // Free allocated memory
  Num *temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }

  return 0;
}
