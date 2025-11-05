#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Before fork...\n");

    int pid = fork();

    if (pid == 0) {
        printf("Child process using exit() -> ");
        printf("This will flush the buffer.\n");
        exit(0);
    } else {
        fork(); // just to show difference
        printf("Child process using _exit() -> ");
        printf("This will NOT flush the buffer.\n");
        _exit(0);
    }

    return 0;
}
