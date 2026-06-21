// B230038CS - Yash Gupta - Lab 3

/* Lab 3. Write a program for Knapsack Problem using Greedy Method.
 * Solve the fractional knapsack problem where items can be broken.
 * Input: weights, profits of items, and total capacity.
 * Output: maximum profit obtained.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int weight;
  int profit;
  float ratio;
} Item;

int compare(const void *a, const void *b) {
  float r1 = ((Item *)a)->ratio;
  float r2 = ((Item *)b)->ratio;
  return (r2 > r1) - (r2 < r1);  // descending order
}

int main() {
  int n = 0, capacity = 0;
  printf("Enter number of items: ");
  scanf("%d", &n);

  Item *items = malloc(n * sizeof(Item));
  printf("Enter profit and weight of each item:\n");
  for (int i = 0; i < n; i++) {
    printf("Item %d (profit weight): ", i + 1);
    scanf("%d %d", &items[i].profit, &items[i].weight);
    items[i].ratio = (float)items[i].profit / items[i].weight;
  }

  printf("Enter knapsack capacity: ");
  scanf("%d", &capacity);

  qsort(items, n, sizeof(Item), compare);

  float totalProfit = 0.0;
  int remaining = capacity;

  for (int i = 0; i < n && remaining > 0; i++) {
    if (items[i].weight <= remaining) {
      totalProfit += items[i].profit;
      remaining -= items[i].weight;
    } else {
      totalProfit += items[i].ratio * remaining;
      remaining = 0;
    }
  }

  printf("Maximum profit: %.2f\n", totalProfit);

  free(items);
  return 0;
}
