// B230038CS - Yash Gupta - Lab 9

/* Lab 9. Write a program for BFS and DFS algorithm.
 * Input: number of vertices, adjacency matrix, and starting node.
 * Output: order of traversal for both BFS and DFS.
 */

#include <stdio.h>

#define MAX 100

int visited[MAX];
int queue[MAX];
int front = -1, rear = -1;

void enqueue(int v) {
  if (rear == MAX - 1)
    return;
  if (front == -1)
    front = 0;
  queue[++rear] = v;
}

int dequeue() {
  if (front == -1 || front > rear)
    return -1;
  return queue[front++];
}

void DFS(int graph[MAX][MAX], int n, int v) {
  visited[v] = 1;
  printf("%d ", v);
  for (int i = 0; i < n; i++) {
    if (graph[v][i] == 1 && !visited[i]) {
      DFS(graph, n, i);
    }
  }
}

void BFS(int graph[MAX][MAX], int n, int start) {
  for (int i = 0; i < n; i++)
    visited[i] = 0;
  enqueue(start);
  visited[start] = 1;

  while (front <= rear) {
    int v = dequeue();
    printf("%d ", v);
    for (int i = 0; i < n; i++) {
      if (graph[v][i] == 1 && !visited[i]) {
        enqueue(i);
        visited[i] = 1;
      }
    }
  }
}

int main() {
  int n;
  int graph[MAX][MAX];

  printf("Enter number of vertices: ");
  scanf("%d", &n);

  printf("Enter adjacency matrix:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &graph[i][j]);
    }
  }

  int start;
  printf("Enter starting vertex (0 to %d): ", n - 1);
  scanf("%d", &start);

  printf("DFS traversal: ");
  for (int i = 0; i < n; i++)
    visited[i] = 0;
  DFS(graph, n, start);
  printf("\n");

  printf("BFS traversal: ");
  front = rear = -1;
  BFS(graph, n, start);
  printf("\n");

  return 0;
}
