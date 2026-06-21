// B230038CS - Yash Gupta - Lab 8
// Prog 8. (a) Write the programs for 1.5 and 2-approximation algorithm of Tasks
// Scheduling

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  int time;
} Task;

int cmp(const void *a, const void *b) {
  return ((Task *)b)->time - ((Task *)a)->time;
}

void schedule_15(Task *tasks, int n, int m) {
  int *machines = (int *)calloc(m, sizeof(int));
  printf("\n1.5-Approximation (Sorted Decreasing):\n");
  qsort(tasks, n, sizeof(Task), cmp);

  for (int i = 0; i < n; i++) {
    int min_idx = 0;
    for (int j = 1; j < m; j++) {
      if (machines[j] < machines[min_idx]) {
        min_idx = j;
      }
    }
    machines[min_idx] += tasks[i].time;
    printf("T%d (time=%d) -> M%d (load=%d)\n", tasks[i].id, tasks[i].time,
           min_idx + 1, machines[min_idx]);
  }

  int makespan = 0;
  for (int i = 0; i < m; i++) {
    if (machines[i] > makespan) {
      makespan = machines[i];
    }
  }
  printf("Makespan: %d\n", makespan);
  free(machines);
}

void schedule_2(Task *tasks, int n, int m) {
  int *machines = (int *)calloc(m, sizeof(int));
  printf("\n2-Approximation (Original Order):\n");

  for (int i = 0; i < n; i++) {
    int min_idx = 0;
    for (int j = 1; j < m; j++) {
      if (machines[j] < machines[min_idx]) {
        min_idx = j;
      }
    }
    machines[min_idx] += tasks[i].time;
    printf("T%d (time=%d) -> M%d (load=%d)\n", tasks[i].id, tasks[i].time,
           min_idx + 1, machines[min_idx]);
  }

  int makespan = 0;
  for (int i = 0; i < m; i++) {
    if (machines[i] > makespan) {
      makespan = machines[i];
    }
  }
  printf("Makespan: %d\n", makespan);
  free(machines);
}

int main() {
  int n, m;
  printf("Enter number of tasks: ");
  scanf("%d", &n);
  printf("Enter number of machines: ");
  scanf("%d", &m);

  Task *tasks = (Task *)malloc(n * sizeof(Task));
  Task *tasks_copy = (Task *)malloc(n * sizeof(Task));

  printf("Enter task times:\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", &tasks[i].time);
    tasks[i].id = i + 1;
    tasks_copy[i] = tasks[i];
  }

  schedule_2(tasks, n, m);
  schedule_15(tasks_copy, n, m);

  free(tasks);
  free(tasks_copy);
  return 0;
}
