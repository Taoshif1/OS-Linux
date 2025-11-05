#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Function to handle SIGINT (Ctrl + C)
void handle_sigint(int sig) {
    printf("\n🛑 Received SIGINT (Ctrl + C). Program will not exit!\n");
}

// Function to handle SIGTERM (termination signal)
void handle_sigterm(int sig) {
    printf("\n⚠️ Received SIGTERM. Gracefully shutting down the process...\n");
    _exit(0);
}

int main() {
    // Register signal handlers
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigterm);

    printf("Process PID = %d\n", getpid());
    printf("Try pressing Ctrl + C or use 'kill -TERM %d' from another terminal.\n", getpid());

    // Keep the program running to test signals
    while (1) {
        printf("Running... press Ctrl + C or send SIGTERM to test.\n");
        sleep(3);
    }

    return 0;
}
