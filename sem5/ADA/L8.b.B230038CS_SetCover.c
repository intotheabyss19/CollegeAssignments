// B230038CS - Yash Gupta - Lab 8
// (b) Write a program for approximation algorithm of Set-Cover Problem.

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  int *elements;
  int size;
  int covered;
} Set;

int is_in_set(int elem, int *arr, int size) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == elem) {
      return 1;
    }
  }
  return 0;
}

int count_uncovered(Set *set, int *covered, int u_size) {
  int count = 0;
  for (int i = 0; i < set->size; i++) {
    if (!is_in_set(set->elements[i], covered, u_size)) {
      count++;
    }
  }
  return count;
}

void set_cover(Set *sets, int n, int *universe, int u_size) {
  int *covered = (int *)malloc(u_size * sizeof(int));
  int c_size = 0;
  int *selected = (int *)calloc(n, sizeof(int));

  printf("\nGreedy Set Cover:\n");

  while (c_size < u_size) {
    int max_cover = 0;
    int max_idx = -1;

    for (int i = 0; i < n; i++) {
      if (selected[i])
        continue;
      int new_cover = count_uncovered(&sets[i], covered, c_size);
      if (new_cover > max_cover) {
        max_cover = new_cover;
        max_idx = i;
      }
    }

    if (max_idx == -1)
      break;

    selected[max_idx] = 1;
    printf("Selected Set %d: { ", sets[max_idx].id);
    for (int i = 0; i < sets[max_idx].size; i++) {
      printf("%d ", sets[max_idx].elements[i]);
      if (!is_in_set(sets[max_idx].elements[i], covered, c_size)) {
        covered[c_size++] = sets[max_idx].elements[i];
      }
    }
    printf("} (covers %d new elements)\n", max_cover);
  }

  printf("\nTotal sets selected: ");
  int total = 0;
  for (int i = 0; i < n; i++) {
    if (selected[i])
      total++;
  }
  printf("%d\n", total);

  free(covered);
  free(selected);
}

int main() {
  int u_size, n;

  printf("Enter size of universe: ");
  scanf("%d", &u_size);

  int *universe = (int *)malloc(u_size * sizeof(int));
  printf("Enter universe elements:\n");
  for (int i = 0; i < u_size; i++) {
    scanf("%d", &universe[i]);
  }

  printf("Enter number of sets: ");
  scanf("%d", &n);

  Set *sets = (Set *)malloc(n * sizeof(Set));

  for (int i = 0; i < n; i++) {
    sets[i].id = i + 1;
    printf("Enter size of set %d: ", i + 1);
    scanf("%d", &sets[i].size);
    sets[i].elements = (int *)malloc(sets[i].size * sizeof(int));
    printf("Enter elements of set %d:\n", i + 1);
    for (int j = 0; j < sets[i].size; j++) {
      scanf("%d", &sets[i].elements[j]);
    }
  }

  set_cover(sets, n, universe, u_size);

  for (int i = 0; i < n; i++) {
    free(sets[i].elements);
  }
  free(sets);
  free(universe);

  return 0;
}
