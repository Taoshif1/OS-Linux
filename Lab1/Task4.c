#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Parent (PID = %d): Starting...\n", getpid());

    for (int i = 1; i <= 3; i++) {
        int pid = fork();

        if (pid == 0) {
            printf("Child %d (PID = %d) is running...\n", i, getpid());
            sleep(1); 
            printf("Child %d (PID = %d) finished.\n", i, getpid());
            return 0;
        }
    }

    // parent waits for all 3 children
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Parent (PID = %d): All children finished. Exiting now.\n", getpid());
    return 0;
}

