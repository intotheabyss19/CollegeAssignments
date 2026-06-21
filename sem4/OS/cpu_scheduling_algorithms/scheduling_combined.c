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

void input(Process *p, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
        p[i].started = 0;
        p[i].priority = 0;
    }
}

void input_priority(Process *p, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time, burst time, and priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
        p[i].started = 0;
    }
}

void display(Process *p, int n, int show_priority) {
    float avg_turnaround = 0, avg_waiting = 0, avg_response = 0;
    
    if (show_priority) {
        printf("\n| PID | Arrival | Burst | Priority | Completion | Turnaround | Waiting | Response |\n");
        printf("|-----|---------|-------|----------|------------|------------|---------|----------|\n");
        
        for (int i = 0; i < n; i++) {
            printf("| P%d  | %7d | %5d | %8d | %10d | %10d | %7d | %8d |\n",
                   p[i].pid, p[i].arrival, p[i].burst, p[i].priority,
                   p[i].completion, p[i].turnaround, p[i].waiting, p[i].response);
            
            avg_turnaround += p[i].turnaround;
            avg_waiting += p[i].waiting;
            avg_response += p[i].response;
        }
    } else {
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
    }
    
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround / n);
    printf("\nAverage Waiting Time: %.2f", avg_waiting / n);
    printf("\nAverage Response Time: %.2f\n", avg_response / n);
}

void fcfs(Process *p, int n) {
    input(p, n);
    
    int time = 0;
    
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
            
        p[i].response = time - p[i].arrival;
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        
        time = p[i].completion;
    }
    
    display(p, n, 0);
}

void sjf(Process *p, int n) {
    input(p, n);
    
    int time = 0, completed = 0;
    int processed[n];
    
    for (int i = 0; i < n; i++) 
        processed[i] = 0;
    
    while (completed < n) {
        int min_burst = 1e9;
        int min_index = -1;
        
        for (int i = 0; i < n; i++) {
            if (!processed[i] && p[i].arrival <= time && p[i].burst < min_burst) {
                min_burst = p[i].burst;
                min_index = i;
            }
        }
        
        if (min_index == -1) {
            time++;
            continue;
        }
        
        processed[min_index] = 1;
        p[min_index].response = time - p[min_index].arrival;
        p[min_index].completion = time + p[min_index].burst;
        p[min_index].turnaround = p[min_index].completion - p[min_index].arrival;
        p[min_index].waiting = p[min_index].turnaround - p[min_index].burst;
        
        time = p[min_index].completion;
        completed++;
    }
    
    display(p, n, 0);
}

void srtf(Process *p, int n) {
    input(p, n);
    
    int time = 0, completed = 0;
    
    while (completed < n) {
        int min_index = -1;
        int min_remaining = 1e9;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].remaining < min_remaining) {
                    min_remaining = p[i].remaining;
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
    
    display(p, n, 0);
}

void priority(Process *p, int n) {
    input_priority(p, n);
    
    int time = 0, completed = 0;
    int processed[n];
    
    for (int i = 0; i < n; i++) 
        processed[i] = 0;
    
    while (completed < n) {
        int highest_priority = 1e9;
        int selected_proc = -1;
        
        for (int i = 0; i < n; i++) {
            if (!processed[i] && p[i].arrival <= time && p[i].priority < highest_priority) {
                highest_priority = p[i].priority;
                selected_proc = i;
            }
        }
        
        if (selected_proc == -1) {
            time++;
            continue;
        }
        
        processed[selected_proc] = 1;
        p[selected_proc].response = time - p[selected_proc].arrival;
        p[selected_proc].completion = time + p[selected_proc].burst;
        p[selected_proc].turnaround = p[selected_proc].completion - p[selected_proc].arrival;
        p[selected_proc].waiting = p[selected_proc].turnaround - p[selected_proc].burst;
        
        time = p[selected_proc].completion;
        completed++;
    }
    
    display(p, n, 1);
}

void round_robin(Process *p, int n) {
    input(p, n);
    
    int quantum;
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    
    int time = 0, completed = 0;
    int remaining[n];
    
    for (int i = 0; i < n; i++) {
        remaining[i] = p[i].burst;
        p[i].started = 0;
    }
    
    while (completed < n) {
        int flag = 0;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && remaining[i] > 0) {
                flag = 1;
                
                if (p[i].started == 0) {
                    p[i].response = time - p[i].arrival;
                    p[i].started = 1;
                }
                
                int exec_time = (remaining[i] < quantum) ? remaining[i] : quantum;
                remaining[i] -= exec_time;
                time += exec_time;
                
                if (remaining[i] == 0) {
                    p[i].completion = time;
                    p[i].turnaround = p[i].completion - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    completed++;
                }
            }
        }
        
        if (flag == 0) {
            time++;
        }
    }
    
    display(p, n, 0);
}

void ljf(Process *p, int n) {
    input(p, n);
    
    int time = 0, completed = 0;
    int processed[n];
    
    for (int i = 0; i < n; i++) 
        processed[i] = 0;
    
    while (completed < n) {
        int max_burst = -1;
        int max_index = -1;
        
        for (int i = 0; i < n; i++) {
            if (!processed[i] && p[i].arrival <= time && p[i].burst > max_burst) {
                max_burst = p[i].burst;
                max_index = i;
            }
        }
        
        if (max_index == -1) {
            time++;
            continue;
        }
        
        processed[max_index] = 1;
        p[max_index].response = time - p[max_index].arrival;
        p[max_index].completion = time + p[max_index].burst;
        p[max_index].turnaround = p[max_index].completion - p[max_index].arrival;
        p[max_index].waiting = p[max_index].turnaround - p[max_index].burst;
        
        time = p[max_index].completion;
        completed++;
    }
    
    display(p, n, 0);
}

int main() {
    int n, choice;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process *p = (Process *)malloc(n * sizeof(Process));
    
    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. FCFS (First Come First Serve)\n");
    printf("2. SJF (Shortest Job First - Non-Preemptive)\n");
    printf("3. SRTF (Shortest Remaining Time First - Preemptive)\n");
    printf("4. Priority (Non-Preemptive)\n");
    printf("5. Round Robin\n");
    printf("6. LJF (Longest Job First - Non-Preemptive)\n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            fcfs(p, n);
            break;
        case 2:
            sjf(p, n);
            break;
        case 3:
            srtf(p, n);
            break;
        case 4:
            priority(p, n);
            break;
        case 5:
            round_robin(p, n);
            break;
        case 6:
            ljf(p, n);
            break;
        default:
            printf("Invalid choice!\n");
            free(p);
            return 1;
    }
    
    free(p);
    return 0;
}
