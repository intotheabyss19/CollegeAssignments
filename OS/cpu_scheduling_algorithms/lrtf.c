#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;        
    int arrival;    
    int burst;      
    int priority;   
    int remaining;  
    int completion; 
    int turnaround; 
    int waiting;    
    int response;   
    int started;    
} Process;

void display(Process *p, int n) {
    float avg_turnaround = 0, avg_waiting = 0, avg_response = 0;
    printf("\n| PID | Arrival | Burst | Completion | Turnaround | Waiting | Response |\n");
    printf("|-----|---------|-------|------------|------------|---------|----------|\n");

    for (int i = 0; i < n; i++) {
        printf("| P%d  | %7d | %5d | %10d | %10d | %7d | %8d |\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting, p[i].response);

        avg_turnaround += p[i].turnaround;
        avg_waiting += p[i].waiting;
        avg_response += p[i].response;
    }

    printf("\nAverage Turnaround Time: %.2f", avg_turnaround / n);
    printf("\nAverage Waiting Time: %.2f", avg_waiting / n);
    printf("\nAverage Response Time: %.2f\n", avg_response / n);
}


void input(Process *p, int n) {
    printf("Enter AT and BT for following processes: \n");
    for (int i = 0; i < n; i++) {
        printf("for P%d: ", i);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].pid = i;
        p[i].remaining = p[i].burst;
        p[i].started = 0;
        p[i].priority = 0;
    }
    display(p, n);
}


void lrtf(Process *p, int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int max_index = -1;
        int max_remaining = -1e9;

        printf("\n");
        for (int i = 0; i < n; i++) {
            if (p[i].arrival < time && p[i].remaining > 0) {
                if (p[i].remaining > max_remaining) {
                    max_remaining = p[i].remaining;
                    max_index = i;
                }
            }
        }

        if (max_index == -1) {
            time++;
            continue;
        }

        if (p[max_index].started == 0) {
            p[max_index].response = time - p[max_index].arrival;
            p[max_index].started = 1;
        }

        p[max_index].remaining--;
        time++;

        if (p[max_index].remaining == 0) {
            p[max_index].completion = time;
            p[max_index].turnaround = p[max_index].completion - p[max_index].arrival;
            p[max_index].waiting = p[max_index].turnaround - p[max_index].burst;
            completed++;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *p = (Process *)malloc(n * sizeof(Process));
    input(p, n);

    lrtf(p, n);
    display(p, n);

    return 0;
}
