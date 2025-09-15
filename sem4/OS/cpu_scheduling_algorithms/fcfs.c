#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid, arrival, burst, remaining, completion, turnaround, waiting, response, started;
} Process;

void input_processes(Process *p, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival and burst time for P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
        p[i].started = 0;
    }
}

void display(Process *p, int n) {
    printf("\n| PID | Arrival | Burst | Completion | Turnaround | Waiting | Response |\n");
    printf("|-----|---------|-------|------------|------------|---------|----------|\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d  | %7d | %5d | %10d | %10d | %7d | %8d |\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting, p[i].response);
    }
}

void fcfs(Process *p, int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        p[i].response = p[i].waiting;
        time = p[i].completion;
    }
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process *p = (Process *)malloc(n * sizeof(Process));
    input_processes(p, n);

    fcfs(p,n);

    display(p, n);
    free(p);
    return 0;
}
