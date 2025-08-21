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

void sjf(Process *p, int n) {
    int time = 0, completed = 0, i, min_burst, min_index;
    int processed[n];
    for (i = 0; i < n; i++) processed[i] = 0;

    while (completed < n) {
        min_burst = 1e9; // Large number
        min_index = -1;

        for (i = 0; i < n; i++) {
            if (!processed[i] && p[i].arrival <= time && p[i].burst < min_burst) {
                min_burst = p[i].burst;
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        i = min_index;
        processed[i] = 1;
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        p[i].response = p[i].waiting;
        time = p[i].completion;
        completed++;
    }
}

void srtf(Process *p, int n) {
    int time = 0, completed = 0, min_index = -1;
    while (completed < n) {
        min_index = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (min_index == -1 || p[i].remaining < p[min_index].remaining) {
                    min_index = i;
                }
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        if (p[min_index].started == 0) {
            p[min_index].response = time - p[min_index].arrival;
            p[min_index].started = 1;
        }

        p[min_index].remaining--;
        time++;

        if (p[min_index].remaining == 0) {
            p[min_index].completion = time;
            p[min_index].turnaround = p[min_index].completion - p[min_index].arrival;
            p[min_index].waiting = p[min_index].turnaround - p[min_index].burst;
            completed++;
        }
    }
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process *p = (Process *)malloc(n * sizeof(Process));
    input_processes(p, n);

    printf("\nChoose Scheduling Algorithm:\n1. FCFS\n2. SJF (Non-Preemptive)\n3. SRTF (Preemptive)\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) fcfs(p, n);
    else if (choice == 2) sjf(p, n);
    else if (choice == 3) srtf(p, n);
    else printf("Invalid choice!\n");

    display(p, n);
    free(p);
    return 0;
}
