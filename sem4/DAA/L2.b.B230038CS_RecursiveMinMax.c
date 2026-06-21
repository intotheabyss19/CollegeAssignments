// B230038CS - Yash Gupta - Lab 2(b)

/* Lab 2(b). Write a program using Divide and Conquer method
 * to find out the maximum and the minimum element from an array.
 */

#include <stdio.h>
#include <stdlib.h>

void MinMaxRecursive(int *arr, int left, int right, int *min, int *max) {
  if (left == right) {
    if (arr[left] < *min) *min = arr[left];
    if (arr[left] > *max) *max = arr[left];
    return;
  }

  if (right == left + 1) {
    if (arr[left] < arr[right]) {
      if (arr[left] < *min) *min = arr[left];
      if (arr[right] > *max) *max = arr[right];
    } else {
      if (arr[right] < *min) *min = arr[right];
      if (arr[left] > *max) *max = arr[left];
    }
    return;
  }

  int mid = (left + right) / 2;
  MinMaxRecursive(arr, left, mid, min, max);
  MinMaxRecursive(arr, mid + 1, right, min, max);
}

int main() {
  int n = 0, *arr;
  printf("Enter n: ");
  scanf("%d", &n);
  arr = calloc(n, sizeof(int));

  printf("Enter the elements of the array: ");
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  int min = arr[0], max = arr[0];
  MinMaxRecursive(arr, 0, n - 1, &min, &max);

  printf("Minimum element: %d\n", min);
  printf("Maximum element: %d\n", max);

  free(arr);
  return 0;
}
