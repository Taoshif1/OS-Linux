#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Parent Process: PID = %d\n", getpid());

    int pid1 = fork();

    if (pid1 == 0) {
        printf("Child 1: PID = %d, PPID = %d\n", getpid(), getppid());
        return 0;
    }

    int pid2 = fork();

    if (pid2 == 0) {
        printf("Child 2: PID = %d, PPID = %d\n", getpid(), getppid());
        return 0;
    }

    int pid3 = fork();

    if (pid3 == 0) {
        printf("Child 3: PID = %d, PPID = %d\n", getpid(), getppid());
        return 0;
    }

    return 0;
}
