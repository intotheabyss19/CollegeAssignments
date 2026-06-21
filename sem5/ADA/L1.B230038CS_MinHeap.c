// B230038CS - Yash Gupta - Lab 1
#include <stdio.h>
#define MAXHEAPSIZE 100
#define HEAPSIZE A[0] // storing heapsize at 0th index of the array
#define SWAP(x, y)                                                             \
  {                                                                            \
    x ^= y;                                                                    \
    y ^= x;                                                                    \
    x ^= y;                                                                    \
  }

// Note: flog, pow2 and printHeap are purely aesthetic function and has nothing
// to do with problem
int flog(int n) {
  n++;
  int i = 0;
  while (n) {
    n /= 2;
    i++;
  }
  return i;
}

int pow2(int n) {
  if (n <= 0)
    return 1;
  n--;
  int i = 2;
  while (n) {
    i *= 2;
    n--;
  }
  return i;
}

void printHeap(int *A) {
  if (HEAPSIZE == 0) {
    printf("Heap is empty\n");
    return;
  }

  int current_index = 1, height = flog(HEAPSIZE);
  int eleline = 1;
  int padding_spaces = pow2(height) / 2;

  // iterating through lines
  for (int line = 0; line <= height; line++) {
    // loop for printing spaces before the elements of the tree
    for (int j = 0; j < padding_spaces; j++) {
      printf("  ");
    }
    // loop for printing the elements and the in-between spaces
    for (int k = 0; k < eleline; k++) {
      if (current_index > HEAPSIZE) {
        break;
      }
      printf("%2d", A[current_index]);
      current_index++;
      // loop for printing in-between spaces
      for (int l = 0; l < padding_spaces * 2 - 1; l++) {
        printf("  ");
      }
    }
    eleline *= 2;
    padding_spaces /= 2;
    printf("\n\n");
  }
}

int Parent(int i) { return i / 2; }
int Left(int i) { return 2 * i; }
int Right(int i) { return 2 * i + 1; }

void MinHeapify(int *A, int i) {
  int l = Left(i);
  int r = Right(i);
  int smallest = i;

  if (l <= HEAPSIZE && A[l] < A[smallest]) {
    smallest = l;
  }
  if (r <= HEAPSIZE && A[r] < A[smallest]) {
    smallest = r;
  }
  if (smallest != i) {
    SWAP(A[i], A[smallest]);
    MinHeapify(A, smallest);
  }
}

void BuildMinHeap(int *A, int length) {
  HEAPSIZE = length;
  for (int i = length / 2; i >= 1; i--)
    MinHeapify(A, i);
}

void MinHeapInsert(int *A, int key) {
  if (HEAPSIZE >=
      MAXHEAPSIZE - 1) { // -1 because index 0 is reserved for heap size
    printf("Error: Heap Overflow\n");
    return;
  }

  HEAPSIZE++;
  int i = HEAPSIZE;
  A[i] = key;

  while (i > 1 && A[Parent(i)] > A[i]) {
    printHeap(A);
    SWAP(A[i], A[Parent(i)]);
    i = Parent(i);
  }
}

int HeapExtractMin(int *A) {
  if (HEAPSIZE < 1) {
    printf("Error: Heap Underflow\n");
    return -1; // Changed from -1e9 to -1 for clarity
  }

  int min = A[1];
  A[1] = A[HEAPSIZE];
  HEAPSIZE--;

  if (HEAPSIZE >= 1) {
    MinHeapify(A, 1);
  }

  return min;
}

int main() {
  // Initialize array with heap size at index 0, followed by heap elements
  int A[MAXHEAPSIZE] = {6, 14, 4, 32, 7, 8, 9}; // First element is heap size

  printf("Original Heap: \n");
  printHeap(A);

  // Build min heap from existing elements (excluding the size at index 0)
  BuildMinHeap(A, A[0]);
  printf("Heap after executing BuildMinHeap(): \n");
  printHeap(A);

  printf("Min value extracted: %d\n", HeapExtractMin(A));
  printf("Heap after extraction: \n");
  printHeap(A);

  int key;
  printf("Enter an element to be inserted: ");
  scanf("%d", &key);
  MinHeapInsert(A, key);
  printf("Heap after adding the element: \n");
  printHeap(A);

  return 0;
}
