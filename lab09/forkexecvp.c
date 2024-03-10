/* Simple program to illustrate the use of fork-exec-wait pattern. 
 * This version uses execvp and command-line arguments to create a new process.
 * To Compile: gcc -Wall forkexecvp.c
 * To Run: ./a.out <command> [args]
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t child_pid = -1; // Global variable to keep track of the child process ID

static void sigint_handler(int sig) {
    // Check if we have a valid child process ID
    if (child_pid > 0) {
        printf("\nSIGINT received. Terminating child process %d\n", child_pid);
        kill(child_pid, SIGTERM); // Send SIGTERM to the child process to terminate it
        // The parent process continues to run, waiting for SIGQUIT
        printf("Use Control-\\ (SIGQUIT) to exit.\n");
    } else {
        printf("\nSIGINT received, but no child process to terminate.\n");
    }
}

void sigtstp_handler(int sig) {
    // Print a message when SIGTSTP is received
    printf("\nSIGTSTP received. Use Control-\\ (SIGQUIT) to exit.\n");
}

void sigquit_handler(int sig) {
    printf("Received quit signal (SIGQUIT), exiting...\n");
    exit(0);
}

int main(int argc, char **argv) {
    //int status;

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    // Set signal handlers
    signal(SIGINT, sigint_handler); // Custom handler for SIGINT to terminate child process
    signal(SIGTSTP, sigtstp_handler); // Custom handler for SIGTSTP
    signal(SIGQUIT, sigquit_handler); // Handle SIGQUIT to exit

    child_pid = fork();
    if (child_pid == 0) { // Child process
        execvp(argv[1], &argv[1]);
        // If execvp fails
        perror("execvp");
        exit(-1);
    } else if (child_pid > 0) { // Parent process
        printf("Parent process running. Waiting for signals.\n");
        // The parent process now waits indefinitely until SIGQUIT is received
        // Instead of waiting for the child process to terminate immediately,
        // it now waits for the child process to be terminated by SIGINT or terminates with SIGQUIT.
        while (1) {
            pause(); // Wait for signals
        }
    } else { // Error in fork
        perror("fork");
        exit(EXIT_FAILURE);
    }


     printf("[%ld]: Exiting program .....\n", (long)getpid());
     return 0;
}
