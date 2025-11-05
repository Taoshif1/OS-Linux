#include <stdio.h>
#include <stdlib.h>

// Define a maximum number of processes for array sizing
#define MAX_PROCESSES 20

int main() {
    int n; // Number of processes
    int bt[MAX_PROCESSES]; // Burst Time array
    int wt[MAX_PROCESSES]; // Waiting Time array
    int tat[MAX_PROCESSES]; // Turnaround Time array
    float avg_wt = 0, avg_tat = 0; // Use float for averages

    printf("--- FCFS CPU SCHEDULING SIMULATOR ---\n");
    printf("Enter total number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    // 1. Input Burst Times
    printf("\nEnter Process Burst Time (in ms)\n");
    for(int i = 0; i < n; i++) {
        printf("P[%d] Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // 2. Calculate Waiting Time (WT)
    wt[0] = 0; // The first process starts immediately (WT=0)

    for(int i = 1; i < n; i++) {
        wt[i] = 0;
        // The waiting time for P[i] is the sum of burst times of all processes before it
        for(int j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
    }

    // 3. Calculate Turnaround Time (TAT) and Total Averages
    printf("\n--- RESULTS ---\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for(int i = 0; i < n; i++) {
        // TAT = WT + BT
        tat[i] = bt[i] + wt[i];
        
        // Sum up total waiting time and total turnaround time
        avg_wt += wt[i];
        avg_tat += tat[i];
        
        printf("P[%d]\t\t%dms\t\t%dms\t\t%dms\n", i + 1, bt[i], wt[i], tat[i]);
    }
    
    // 4. Compute Averages
    avg_wt /= n;
    avg_tat /= n;

    printf("\n=======================================================");
    printf("\nAverage Waiting Time: %.2fms", avg_wt);
    printf("\nAverage Turnaround Time: %.2fms", avg_tat);
    printf("\n=======================================================\n");

    return 0;
}
