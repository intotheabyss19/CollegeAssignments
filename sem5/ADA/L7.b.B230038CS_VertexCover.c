// B230038CS - Yash Gupta - Lab 7
// Write a program for 2-approximation algorithm of Vertex-Cover Problem.

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct Node {
  int key;
  struct Node *next;
} node;

node *newNode(int key) {
  node *newnode = malloc(sizeof(node));
  newnode->key = key;
  newnode->next = NULL;
  return newnode;
}

void addEdge(node *G[], int u, int v) {
  node *n1 = newNode(v);
  n1->next = G[u];
  G[u] = n1;

  node *n2 = newNode(u);
  n2->next = G[v];
  G[v] = n2;
}

void inputG(node *G[], int n) {
  int e, u, v;
  printf("Enter number of edges: ");
  scanf("%d", &e);

  printf("Enter each edge as two vertex indices (u v):\n");
  for (int i = 0; i < e; i++) {
    scanf("%d %d", &u, &v);
    if (u >= n || v >= n || u < 0 || v < 0) {
      printf("Invalid vertices! Skipping edge.\n");
      continue;
    }
    addEdge(G, u, v);
  }
}

void printGraph(node *G[], int n) {
  printf("\nGraph adjacency list:\n");
  for (int i = 0; i < n; i++) {
    printf("%d -> ", i);
    node *temp = G[i];
    while (temp != NULL) {
      printf("%d ", temp->key);
      temp = temp->next;
    }
    printf("\n");
  }
}

void vertexCover(node *G[], int n) {
  int visited[MAXSIZE] = {0};
  int cover[MAXSIZE];
  int coverSize = 0;

  for (int u = 0; u < n; u++) {
    if (!visited[u]) {
      node *v = G[u];
      while (v != NULL) {
        if (!visited[v->key]) {
          visited[u] = 1;
          visited[v->key] = 1;
          cover[coverSize++] = u;
          cover[coverSize++] = v->key;
          break;
        }
        v = v->next;
      }
    }
  }

  printf("\nApproximate Vertex Cover: ");
  for (int i = 0; i < coverSize; i++) {
    printf("%d ", cover[i]);
  }
  printf("\n");
}

int main() {
  int n;
  node *G[MAXSIZE] = {NULL};

  printf("Enter number of vertices: ");
  scanf("%d", &n);

  inputG(G, n);
  printGraph(G, n);
  vertexCover(G, n);

  return 0;
}
