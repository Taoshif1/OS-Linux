#include <stdio.h>

int main() {
    int n, tq, bt[20], rem_bt[20], wt[20], tat[20], i, time = 0;
    int count = 0, flag = 0;
    float avg_wt = 0, avg_tat = 0;
    
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    
    printf("\nEnter Process Burst Times\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];  // Store remaining burst time
        wt[i] = 0;  // Initialize waiting time
    }
    
    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);
    
    printf("\n=== GANTT CHART ===\n| ");
    
    // Round Robin scheduling logic
    while(1) {
        flag = 0;  // To check if all processes are done
        
        for(i = 0; i < n; i++) {
            if(rem_bt[i] > 0) {
                flag = 1;  // At least one process is remaining
                
                if(rem_bt[i] > tq) {
                    // Process executes for time quantum
                    printf("P%d | ", i + 1);
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    // Process executes for remaining time and completes
                    printf("P%d | ", i + 1);
                    time += rem_bt[i];
                    
                    // Calculate waiting and turnaround time when process completes
                    wt[i] = time - bt[i];
                    tat[i] = time;
                    
                    rem_bt[i] = 0;
                    count++;
                }
            }
        }
        
        // If all processes are done, break
        if(flag == 0)
            break;
    }
    
    printf("\n");
    
    // Display detailed results
    printf("\n=== EXECUTION DETAILS ===\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    for(i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        
        printf("P[%d]\t\t%d\t\t%d\t\t%d\n", 
               i + 1, bt[i], wt[i], tat[i]);
    }
    
    avg_wt /= n;
    avg_tat /= n;
    
    printf("\n=== RESULTS ===");
    printf("\nAverage Waiting Time: %.2f ms", avg_wt);
    printf("\nAverage Turnaround Time: %.2f ms\n", avg_tat);
    
    return 0;
}
