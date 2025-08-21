// B230038CS - Yash Gupta - Lab 8

/* Lab 8. Write a program for Optimal Binary Search Tree using Dynamic
 * Programming. Given the probabilities of searching keys, compute the minimum
 * cost of an optimal BST. Input: number of keys, key list, and search
 * probabilities. Output: minimum search cost.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF 1e9

float min(float a, float b) { return (a < b) ? a : b; }

int main() {
  int n;
  printf("Enter number of keys: ");
  scanf("%d", &n);

  int *keys = malloc((n + 1) * sizeof(int));
  float *p = malloc((n + 1) * sizeof(float)); // search probabilities

  printf("Enter keys in sorted order:\n");
  for (int i = 1; i <= n; i++) {
    printf("Key %d: ", i);
    scanf("%d", &keys[i]);
  }

  printf("Enter search probabilities for each key:\n");
  for (int i = 1; i <= n; i++) {
    printf("p[%d]: ", i);
    scanf("%f", &p[i]);
  }

  float cost[n + 2][n + 1]; // cost[][] stores cost of optimal BST from i to j
  float sum[n + 1][n + 1];  // sum[[] stores sum of probabilities from i to j

  for (int i = 1; i <= n; i++) {
    cost[i][i - 1] = 0;
    cost[i][i] = p[i];
    sum[i][i - 1] = 0;
    sum[i][i] = p[i];
  }
  cost[n + 1][n] = 0;

  for (int l = 2; l <= n; l++) {
    for (int i = 1; i <= n - l + 1; i++) {
      int j = i + l - 1;
      cost[i][j] = INF;
      sum[i][j] = sum[i][j - 1] + p[j];

      for (int r = i; r <= j; r++) {
        float c = cost[i][r - 1] + cost[r + 1][j] + sum[i][j];
        if (c < cost[i][j]) {
          cost[i][j] = c;
        }
      }
    }
  }

  printf("Minimum cost of Optimal BST: %.2f\n", cost[1][n]);

  free(keys);
  free(p);
  return 0;
}
