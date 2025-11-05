#include <stdio.h>

#define MAX_PROCESSES 20

typedef struct {
    int pid;       // Process ID
    int bt;        // Burst Time
    int priority;  // Priority
    int wt;        // Waiting Time
    int tat;       // Turnaround Time
} Process;

int main() {
    Process p[MAX_PROCESSES];
    int n;
    float avg_wt = 0, avg_tat = 0;

    printf("--- PRIORITY CPU SCHEDULING SIMULATOR ---\n");
    printf("Enter total number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    // Input burst time and priority
    printf("\nEnter Burst Time and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P[%d] Burst Time: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("P[%d] Priority: ", i + 1);
        scanf("%d", &p[i].priority);
    }

    // Sort processes by priority (ascending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority > p[j].priority) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Waiting Time
    p[0].wt = 0;
    for (int i = 1; i < n; i++) {
        p[i].wt = 0;
        for (int j = 0; j < i; j++)
            p[i].wt += p[j].bt;
    }

    // Calculate Turnaround Time and averages
    printf("\n--- RESULTS ---\n");
    printf("Process\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;

        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].priority, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\n=======================================================");
    printf("\nAverage Waiting Time: %.2fms", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2fms", avg_tat / n);
    printf("\n=======================================================\n");

    return 0;
}
