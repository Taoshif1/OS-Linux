#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
#define HISTORY_SIZE 10

void add_to_history(char history[HISTORY_SIZE][MAX_INPUT], int *count, const char *cmd) {
    if (strlen(cmd) == 0) return; // skip empty commands

    // Shift if history full
    if (*count == HISTORY_SIZE) {
        for (int i = 1; i < HISTORY_SIZE; i++) {
            strcpy(history[i - 1], history[i]);
        }
        (*count)--;
    }

    strcpy(history[*count], cmd);
    (*count)++;
}

void show_history(char history[HISTORY_SIZE][MAX_INPUT], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d %s\n", i + 1, history[i]);
    }
}

int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    char history[HISTORY_SIZE][MAX_INPUT];
    int history_count = 0;

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

        // Skip empty input
        if (strlen(input) == 0)
            continue;

        // Exit command
        if (strcmp(input, "exit") == 0)
            break;

        // Add to history
        add_to_history(history, &history_count, input);

        // --- Handle "history" command ---
        if (strcmp(input, "history") == 0) {
            show_history(history, history_count);
            continue;
        }

        // Tokenize input
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // --- Handle "cd" command manually ---
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "mysh: expected argument to \"cd\"\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("mysh");
                }
            }
            continue;
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
