// B230038CS - Yash Gupta - Lab 4

/* Lab 4: Write a program for Prim’s Algorithm to find out Minimum Spanning Tree
 * (MST) from a given weighted graph
 */

#include <stdio.h>
#define V 5
#define INF 1000000

int minKey(int key[], int inMST[]) {
  int min = INF, min_index = -1;
  for (int v = 0; v < V; v++)
    if (!inMST[v] && key[v] < min)
      min = key[v], min_index = v;
  return min_index;
}

void printMST(int parent[], int graph[V][V]) {
  printf("Edge   Weight\n");
  for (int i = 1; i < V; i++)
    printf("%d - %d    %d\n", parent[i], i, graph[i][parent[i]]);
}

void primMST(int graph[V][V]) {
  int parent[V], key[V], inMST[V];
  for (int i = 0; i < V; i++)
    key[i] = INF, inMST[i] = 0;
  key[0] = 0;
  parent[0] = -1;
  for (int count = 0; count < V - 1; count++) {
    int u = minKey(key, inMST);
    inMST[u] = 1;
    for (int v = 0; v < V; v++)
      if (graph[u][v] && !inMST[v] && graph[u][v] < key[v])
        parent[v] = u, key[v] = graph[u][v];
  }
  printMST(parent, graph);
}

int main() {
  int graph[V][V] = {
      {0, 2, 0, 6, 0}, {2, 0, 3, 8, 5}, {0, 3, 0, 0, 7},
      {6, 8, 0, 0, 9}, {0, 5, 7, 9, 0},
  };
  primMST(graph);
  return 0;
}
