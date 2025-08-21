// B230038CS - Yash Gupta - Lab 1

/* Lab 1. A function f(m,n) is defined for all non-negative values of m and n as follows:
 * f(m,n) = { n + 1,                 if m = 0}
 *          { f(m-1, 1),             if m != 0 and n = 0}
 *          { f(m-1, f(m, n-1)),     if m != 0 and n != 0}
 * Write a recursive algorithm to compute f(m,n). Test the output of the function f(1,3).
 */

#include <stdio.h>

int f(int m, int n) {
  if (m == 0) return n + 1;
  else if (n == 0) return f(m - 1, 1);
  else return f (m - 1, f(m, n - 1));
}

int main() {
  int m = 0, n = 0;
  printf("Enter m, n: ");
  scanf("%d %d", &m, &n);
  printf("Value of f(%d,%d) is : %d\n", m, n, f(m, n));
  return 0;
}
