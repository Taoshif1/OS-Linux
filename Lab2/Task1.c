#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    while (1) {
        printf("mysh> ");
        fflush(stdout);

        // Get user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        // Exit command
        if (strcmp(input, "exit") == 0)
            break;

        // Tokenize input
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Skip empty input
        if (args[0] == NULL)
            continue;

        // --- Handle "cd" command manually ---
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "mysh: expected argument to \"cd\"\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("mysh");
                }
            }
            continue; // skip fork() for "cd"
        }

        // --- Create new process for other commands ---
        pid = fork();

        if (pid == 0) {
            // Child Process
            if (execvp(args[0], args) == -1) {
                perror("mysh");
                exit(EXIT_FAILURE);
            }
        } else if (pid > 0) {
            // Parent waits
            waitpid(pid, &status, 0);
        } else {
            perror("fork failed");
        }
    }

    return 0;
}
