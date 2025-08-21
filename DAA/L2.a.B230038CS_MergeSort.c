// B230038CS - Yash Gupta - Lab 2(a)

/* Lab 2(a). Write a program for Merge Sort algorithm */

#include <stdio.h>
#include <stdlib.h>

void Merge(int *arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  int *L = malloc(n1 * sizeof(int));
  int *R = malloc(n2 * sizeof(int));

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }

  while (i < n1) {
    arr[k++] = L[i++];
  }

  while (j < n2) {
    arr[k++] = R[j++];
  }

  free(L);
  free(R);
}

void MergeSort(int *arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    MergeSort(arr, left, mid);
    MergeSort(arr, mid + 1, right);
    Merge(arr, left, mid, right);
  }
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

  MergeSort(arr, 0, n - 1);

  printf("Sorted array: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  free(arr);
  return 0;
}
