#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Parent (PID = %d) starting...\n", getpid());

    for (int i = 1; i <= 3; i++) {
        int pid = fork();

        if (pid == 0) {
            // Child process
            sleep(3); // wait until parent exits
            printf("Child %d (PID = %d) adopted by (PPID = %d)\n", i, getpid(), getppid());
            return 0;
        }
    }

    // Parent exits early before children finish
    printf("Parent (PID = %d) exiting before children...\n", getpid());
    return 0;
}
