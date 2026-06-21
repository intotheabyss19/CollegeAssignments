// B230038CS - Yash Gupta - L7

/* Lab 7. Write a program for matrix-chain multiplication problem based on
 * dynamic programming.
 */

#include <limits.h>
#include <stdio.h>
#define MAX_N 50

void matrixChainOrder(int p[], int n, int m[MAX_N][MAX_N],
                      int s[MAX_N][MAX_N]) {
  for (int i = 1; i <= n; i++)
    m[i][i] = 0;
  for (int L = 2; L <= n; L++) {
    for (int i = 1; i <= n - L + 1; i++) {
      int j = i + L - 1;
      m[i][j] = INT_MAX;
      for (int k = i; k < j; k++) {
        int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
        if (cost < m[i][j]) {
          m[i][j] = cost;
          s[i][j] = k;
        }
      }
    }
  }
}

void printOptimalParents(int s[MAX_N][MAX_N], int i, int j) {
  if (i == j) {
    printf("A%d", i);
  } else {
    printf("(");
    printOptimalParents(s, i, s[i][j]);
    printOptimalParents(s, s[i][j] + 1, j);
    printf(")");
  }
}

int main() {
  int n, p[MAX_N];
  scanf("%d", &n);
  for (int i = 0; i <= n; i++)
    scanf("%d", &p[i]);
  static int m[MAX_N][MAX_N], s[MAX_N][MAX_N];
  matrixChainOrder(p, n, m, s);
  printf("Minimum number of multiplications: %d\n", m[1][n]);
  printf("Optimal parenthesization: ");
  printOptimalParents(s, 1, n);
  printf("\n");
  return 0;
}
