#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Parent (PID = %d) starting...\n", getpid());

    for (int i = 1; i <= 2; i++) {
        int pid = fork();

        if (pid == 0) {
            printf("Child %d (PID = %d) is exiting...\n", i, getpid());
            exit(0); // Child exits immediately
        }
    }

    // Parent doesn’t call wait() -> children become zombies
    printf("Parent (PID = %d): Sleeping... check zombie status using 'ps -el' in another terminal.\n", getpid());
    sleep(10); // Gives time to observe zombies

    printf("Parent (PID = %d): Exiting now.\n", getpid());
    return 0;
}
