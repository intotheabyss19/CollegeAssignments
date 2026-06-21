// B230038CS - Yash Gupta - Lab 7
// Prog 7. (a) Write a program for 2-approximation algorithm of Travelling
// Salesperson Problem.

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int u;
  int v;
  int w;
} Edge;

int find_parent(int node, int *parent) {
  if (parent[node] != node) {
    parent[node] = find_parent(parent[node], parent);
  }
  return parent[node];
}

void union_set(int u, int v, int *parent, int *rank) {
  int pu = find_parent(u, parent);
  int pv = find_parent(v, parent);
  if (rank[pu] < rank[pv]) {
    parent[pu] = pv;
  } else if (rank[pu] > rank[pv]) {
    parent[pv] = pu;
  } else {
    parent[pv] = pu;
    rank[pu]++;
  }
}

int cmp_edge(const void *a, const void *b) {
  return ((Edge *)a)->w - ((Edge *)b)->w;
}

void dfs(int node, int **adj, int n, int *visited, int *tour, int *idx) {
  visited[node] = 1;
  tour[(*idx)++] = node;
  for (int i = 0; i < n; i++) {
    if (adj[node][i] && !visited[i]) {
      dfs(i, adj, n, visited, tour, idx);
    }
  }
}

void tsp_2approx(int **graph, int n) {
  Edge *edges = (Edge *)malloc(n * n * sizeof(Edge));
  int e_count = 0;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (graph[i][j] > 0) {
        edges[e_count].u = i;
        edges[e_count].v = j;
        edges[e_count].w = graph[i][j];
        e_count++;
      }
    }
  }

  qsort(edges, e_count, sizeof(Edge), cmp_edge);

  int *parent = (int *)malloc(n * sizeof(int));
  int *rank = (int *)calloc(n, sizeof(int));
  int **mst = (int **)calloc(n, sizeof(int *));
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    mst[i] = (int *)calloc(n, sizeof(int));
  }

  printf("\nMST Edges:\n");
  int mst_cost = 0;
  int mst_edges = 0;

  for (int i = 0; i < e_count && mst_edges < n - 1; i++) {
    int u = edges[i].u;
    int v = edges[i].v;
    int w = edges[i].w;

    if (find_parent(u, parent) != find_parent(v, parent)) {
      union_set(u, v, parent, rank);
      mst[u][v] = w;
      mst[v][u] = w;
      printf("Edge %d-%d: %d\n", u, v, w);
      mst_cost += w;
      mst_edges++;
    }
  }

  printf("MST Cost: %d\n", mst_cost);

  int *visited = (int *)calloc(n, sizeof(int));
  int *tour = (int *)malloc((n + 1) * sizeof(int));
  int idx = 0;

  dfs(0, mst, n, visited, tour, &idx);
  tour[idx] = 0;

  printf("\nHamiltonian Tour (preorder): ");
  int total_cost = 0;
  for (int i = 0; i <= idx; i++) {
    printf("%d ", tour[i]);
    if (i < idx) {
      total_cost += graph[tour[i]][tour[i + 1]];
    }
  }
  printf("\nTour Cost: %d\n", total_cost);
  printf("Approximation Ratio: %.2f\n", (float)total_cost / mst_cost);

  for (int i = 0; i < n; i++) {
    free(mst[i]);
  }
  free(mst);
  free(edges);
  free(parent);
  free(rank);
  free(visited);
  free(tour);
}

int main() {
  int n;
  printf("Enter number of vertices: ");
  scanf("%d", &n);

  int **graph = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    graph[i] = (int *)malloc(n * sizeof(int));
  }

  printf("Enter adjacency matrix:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &graph[i][j]);
    }
  }

  tsp_2approx(graph, n);

  for (int i = 0; i < n; i++) {
    free(graph[i]);
  }
  free(graph);

  return 0;
}
