// B230038CS - Yash Gupta - Lab 4

/* Lab 4: Write a program for Prim’s Algorithm to find out Minimum Spanning Tree
 * (MST) from a given weighted graph
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 1000
#define MAX_VERTICES 100

typedef struct {
  int u, v, w;
} Edge;
int parent[MAX_VERTICES], rankArr[MAX_VERTICES];

int findSet(int x) {
  if (parent[x] != x)
    parent[x] = findSet(parent[x]);
  return parent[x];
}

void unionSet(int a, int b) {
  a = findSet(a);
  b = findSet(b);
  if (a == b)
    return;
  if (rankArr[a] < rankArr[b])
    parent[a] = b;
  else if (rankArr[b] < rankArr[a])
    parent[b] = a;
  else {
    parent[b] = a;
    rankArr[a]++;
  }
}

int cmpEdge(const void *a, const void *b) {
  return ((Edge *)a)->w - ((Edge *)b)->w;
}

void kruskalMST(Edge edges[], int E, int V) {
  qsort(edges, E, sizeof(Edge), cmpEdge);
  for (int i = 0; i < V; i++) {
    parent[i] = i;
    rankArr[i] = 0;
  }
  int cnt = 0, i = 0;
  printf("Edge   Weight\n");
  while (cnt < V - 1 && i < E) {
    Edge e = edges[i++];
    int uRoot = findSet(e.u), vRoot = findSet(e.v);
    if (uRoot != vRoot) {
      printf("%d - %d    %d\n", e.u, e.v, e.w);
      unionSet(uRoot, vRoot);
      cnt++;
    }
  }
}

int main() {
  int V = 4, E = 5;
  Edge edges[] = {
      {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4},
  };
  kruskalMST(edges, E, V);
  return 0;
}
