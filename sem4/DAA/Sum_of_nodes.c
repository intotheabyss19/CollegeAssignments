/* Given a binary tree T, Write a recursive algorithm to calculate the sum of
 * all the node's values */

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node {
  int key;
  struct node *left;
  struct node *right;
} node;

node *newNode(int key) {
  node *temp = malloc(sizeof(node));
  temp->key = key;
  temp->left = NULL;
  temp->right = NULL;
}

void addBT(int n, int a[]) {

  for (int i = 0; i < n; i++) {
  }
}

int main() {
  int n;
  int a[MAX];
  node *bt;
  printf("Enter n: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  for (int j = 0; j < n; j++) {
    printf("%d ", a[j]);
  }
  printf("\n");
  return 0;
}
