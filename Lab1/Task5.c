#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    printf("Parent (PID = %d): Starting...\n", getpid());

    for (int i = 1; i <= 3; i++) {
        int pid = fork();

        if (pid == 0) {

            printf("Child %d (PID = %d) started.\n", i, getpid());
            sleep(i * 2); 	// each child sleeps longer (2s, 4s, 6s)
            printf("Child %d (PID = %d) finished after %d seconds.\n", i, getpid(), i * 2);
            return 0;
        }
    }

    // Parent waits for all children
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    printf("Parent (PID = %d): All children finished. Exiting now.\n", getpid());
    return 0;
}
