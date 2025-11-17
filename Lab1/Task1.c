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

========================================================================================
// #include <stdio.h>
// #include <unistd.h>

// int main() {
//     printf("Parent Process: PID = %d\n", getpid());

//     for (int i = 1; i <= 3; i++) {
//         int pid = fork();

//         if (pid == 0) {  
//             // Child process
//             printf("Child %d: PID = %d, PPID = %d\n", i, getpid(), getppid());
//             return 0; // Child exits so it doesn't continue loop
//         }
//     }

//     return 0; // Parent ends
// }
