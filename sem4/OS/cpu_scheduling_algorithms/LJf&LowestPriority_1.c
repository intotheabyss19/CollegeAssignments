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
    printf("Enter AT and BT for following processes");
    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
        p[i].started = 0;
        p[i].priority = 0;
    }
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
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);



}
