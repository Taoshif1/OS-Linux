#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    printf("Parent (PID = %d) starting...\n", getpid());

    int pid1 = fork(); // Orphan
    if (pid1 == 0) {
        sleep(2);
        printf(" Orphan child (PID = %d), adopted by (PPID = %d)\n", getpid(), getppid());
        exit(0);
    }

    int pid2 = fork(); // Zombie
    if (pid2 == 0) {
        printf(" Zombie child (PID = %d) exiting but parent won't wait.\n", getpid());
        _exit(0);
    }

    int pid3 = fork(); // Normal child
    if (pid3 == 0) {
        printf(" Normal child (PID = %d) running...\n", getpid());
        sleep(1);
        printf(" Normal child (PID = %d) finished.\n", getpid());
        exit(0);
    }

    // Parent creates orphan by exiting early for first child
    sleep(1);
    waitpid(pid3, NULL, 0); // wait for normal child only
    printf("Parent (PID = %d) exiting now (orphan and zombie remain temporarily)\n", getpid());
    return 0;
}

