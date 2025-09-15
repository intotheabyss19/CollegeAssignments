// B230038CS - Q15 - A5
#include <stdio.h>
#include <stdlib.h>

void minHeapify(double arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest]) 
	    smallest = left;
    if (right < n && arr[right] < arr[smallest]) 
	    smallest = right;

    if (smallest != i) {
        double temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap(double arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) 
	    minHeapify(arr, n, i);
}

void heapsort(double arr[], int n) {
    buildMinHeap(arr, n);

    for (int i = n - 1; i > 0; i--) {
        double temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        minHeapify(arr, i, 0);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <real numbers>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    double *arr = malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) 
	    arr[i] = atof(argv[i + 1]);

    heapsort(arr, n);

    for (int i = 0; i < n; i++) 
	    printf("%g ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
