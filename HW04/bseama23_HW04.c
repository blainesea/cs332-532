/*
Blaine Seaman
bseama23
cs332 HW4

To compile: gcc -o myscheduler bseama23_HW04.c 
To run: ./myscheduler <number of jobs that can run concurrently>
    ex: ./myscheduler 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_JOBS 100

typedef struct {
    int jobid;
    char command[256];
    pid_t pid;
    char status[10]; // "Running", "Waiting", or "Completed"
} Job;

Job jobQueue[MAX_JOBS];
int totalJobs = 0;
int currentJobId = 1;
int runningJobs = 0;
int P; // Maximum parallel jobs

void addJob(char* command, pid_t pid, char* status) {
    if (totalJobs < MAX_JOBS) {
        jobQueue[totalJobs].jobid = currentJobId++;
        strncpy(jobQueue[totalJobs].command, command, sizeof(jobQueue[totalJobs].command) - 1);
        jobQueue[totalJobs].pid = pid;
        strncpy(jobQueue[totalJobs].status, status, sizeof(jobQueue[totalJobs].status) - 1);
        totalJobs++;
    } else {
        printf("Job queue is full.\n");
    }
}

void updateJobStatus(pid_t pid, char* status) {
    for (int i = 0; i < totalJobs; i++) {
        if (jobQueue[i].pid == pid) {
            strncpy(jobQueue[i].status, status, sizeof(jobQueue[i].status) - 1);
            break;
        }
    }
}

void executeWaitingJobs() {
    for (int i = 0; i < totalJobs && runningJobs < P; i++) {
        if (strcmp(jobQueue[i].status, "Waiting") == 0) {
            // Simulate moving waiting jobs to running state
            jobQueue[i].pid = fork();
            if (jobQueue[i].pid == 0) { // Child process
                char* args[] = {"/bin/sh", "-c", jobQueue[i].command, NULL};
                execv("/bin/sh", args);
                exit(EXIT_FAILURE); // Only reached if execv fails
            } else if (jobQueue[i].pid > 0) {
                strcpy(jobQueue[i].status, "Running");
                runningJobs++;
                printf("Job %d is now running.\n", jobQueue[i].jobid);
            } else {
                perror("fork");
            }
        }
    }
}

void executeJob(char* fullCommand) {
    if (runningJobs < P) {
        pid_t pid = fork();
        if (pid == 0) { // Child process
            char* args[] = {"/bin/sh", "-c", fullCommand, NULL};
            execv("/bin/sh", args);
            exit(EXIT_FAILURE); // execv fails
        } else if (pid > 0) {
            addJob(fullCommand, pid, "Running");
            runningJobs++;
            printf("Job %d is now running.\n", currentJobId - 1);
        } else {
            perror("fork");
        }
    } else {
        addJob(fullCommand, -1, "Waiting");
        printf("Job %d is waiting for execution.\n", currentJobId - 1);
    }
}

void showJobs() {
    printf("jobid command status\n");
    for (int i = 0; i < totalJobs; i++) {
        printf("%d %s %s\n", jobQueue[i].jobid, jobQueue[i].command, jobQueue[i].status);
    }
}

void checkCompletedJobs() {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        updateJobStatus(pid, "Completed");
        runningJobs--;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <max_parallel_jobs>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    P = atoi(argv[1]);
    printf("Job scheduler started with capacity for %d concurrent jobs.\n", P);

    char commandLine[1024];
    while (1) {
        checkCompletedJobs();
        executeWaitingJobs();

        printf("Enter command> ");
        if (fgets(commandLine, sizeof(commandLine), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }
        commandLine[strcspn(commandLine, "\n")] = 0; // Remove newline

        if (strncmp(commandLine, "submit ", 7) == 0) {
            executeJob(commandLine + 7);
        } else if (strcmp(commandLine, "showjobs") == 0) {
            showJobs();
        } else {
            printf("Unknown command.\n");
        }
    }

    return 0;
}