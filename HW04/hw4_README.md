# Compilation Instructions

If you're a make file
```bash
make # this will compile all the files
make run # this will run all the files
```

If you're not using a make file
```bash
To Compile: gcc -o myscheduler bseama23_HW04.c 

To Run: ./myscheduler <number of jobs that can run concurrently>
    Example: ./myscheduler 2
```

# My Files

### typedef struct     (Job)
This structure represents a job in the job queue. It includes the job ID (jobid), the command to execute (command), the process ID (pid), and the job's current status (status), which can be either "Running", "Waiting", or "Completed".

### void addJob(char* command, pid_t pid, char* status)
This function adds a new job to the job queue. It assigns a unique job ID, stores the command, sets the initial process ID, and marks the status as either "Waiting" or "Running", depending on what processes have previously been submitted. 

### void updateJobStatus(pid_t pid, char* status)
This function updates the status of a job based on its process ID. It's used to mark jobs as "Completed" or change their status from "Waiting" to "Running".

### void executeWaitingJobs(int P)
This function monitors the queue and execute jobs that are waiting, depending on the availability of execution slots (defined by the user through the command line). 

### void executeJob(char* fullCommand)
This function executes a job if execution slots are available. Otherwise it will queue the job with a "Waiting" status. It also initiates the actual command execution using fork() and exec().

### void showJobs()
Prints out an overview of all scheduled jobs along with their IDs, commands, and current statuses

### void checkCompletedJobs()
Regularly checks for and updates the statuses of jobs that have executed, marking them "Completed" and opening execution slots for pending jobs.

### int main(int argc, char *argv[])
The main function of the program. It begins by setting the maximum number of jobs that can run concurrently by prompting the user. Then, it enters a loop where it checks for and updates the status of any completed jobs, attempts to start any jobs that were waiting for available slots, and prompts the user to enter commands. Users can submit new jobs for execution or request a list of all jobs along with their statuses by entering specific commands. The scheduler dynamically manages job execution based on the specified concurrency limit.

# Github repo link
https://github.com/blainesea/cs332-532

# References

I used the Lab Workbook and the given files as a starting point for this program. 

I used this article for assistance with understanding the concepts behind multi-threading: 
    https://www.geeksforgeeks.org/multithreading-in-c/