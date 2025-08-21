// B230038CS - Yash Gupta - Lab 6

/* Lab 6. Given a set of n number of jobs, J = {j1, j2, ..., jn} and p number of
 * identical machines M = {m1, m2,..., mp}, write a program using greedy mathod
 * to assign the jobs to the machines such that overall completion time
 * (makespan) of the jobs will be minimum. Consider the job jk has execution
 * time tk for all k = 1, 2,..., n.
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_JOBS 100
#define MAX_MACHINES 10

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int cmpDesc(const void *a, const void *b) { return (*(int *)b) - (*(int *)a); }

int findMinLoadMachine(int load[], int m) {
  int idx = 0;
  for (int i = 1; i < m; i++)
    if (load[i] < load[idx])
      idx = i;
  return idx;
}

void scheduleLPT(int jobs[], int n, int m) {
  int load[MAX_MACHINES] = {0}, assignment[MAX_JOBS];
  qsort(jobs, n, sizeof(int), cmpDesc);
  for (int i = 0; i < n; i++) {
    int machine = findMinLoadMachine(load, m);
    assignment[i] = machine;
    load[machine] += jobs[i];
  }
  printf("Job\tTime\tMachine\n");
  for (int i = 0; i < n; i++)
    printf("%d\t%d\tM%d\n", i + 1, jobs[i], assignment[i] + 1);
  int makespan = load[0];
  for (int i = 1; i < m; i++)
    if (load[i] > makespan)
      makespan = load[i];
  printf("Makespan: %d\n", makespan);
}

int main() {
  int n, m, jobs[MAX_JOBS];
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", &jobs[i]);
  scheduleLPT(jobs, n, m);
  return 0;
}
