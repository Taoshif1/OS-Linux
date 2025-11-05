#include <stdio.h>

int main() {
    int n, bt[20], wt[20], tat[20], p[20], i, j, temp;
    float avg_wt = 0, avg_tat = 0;
    
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    
    printf("\nEnter Process Burst Time and Priority\n");
    printf("(Lower number = Higher priority)\n");
    
    for(i = 0; i < n; i++) {
        printf("P[%d] Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P[%d] Priority: ", i + 1);
        scanf("%d", &p[i]);
    }
    
    // Store original process numbers for display
    int process[20];
    for(i = 0; i < n; i++) {
        process[i] = i + 1;
    }
    
    // Sort processes by priority (ascending order - lower number = higher priority)
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(p[j] > p[j + 1]) {
                // Swap priorities
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
                
                // Swap burst times
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
                
                // Swap process numbers
                temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
    
    // Calculate waiting time (same as FCFS after sorting)
    wt[0] = 0;
    for(i = 1; i < n; i++) {
        wt[i] = 0;
        for(j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
    }
    
    // Display Gantt Chart
    printf("\n=== GANTT CHART ===\n");
    printf("| ");
    for(i = 0; i < n; i++) {
        printf("P%d | ", process[i]);
    }
    printf("\n");
    
    printf("0  ");
    int time = 0;
    for(i = 0; i < n; i++) {
        time += bt[i];
        printf("%d  ", time);
    }
    printf("\n");
    
    // Display results table
    printf("\n=== EXECUTION ORDER (By Priority) ===\n");
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    
    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
        
        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               process[i], bt[i], p[i], wt[i], tat[i]);
    }
    
    avg_wt /= n;
    avg_tat /= n;
    
    printf("\n=== RESULTS ===");
    printf("\nAverage Waiting Time: %.2f ms", avg_wt);
    printf("\nAverage Turnaround Time: %.2f ms\n", avg_tat);
    
    return 0;
}
