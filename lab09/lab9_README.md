# Compilation Instructions

If you're a make file
```bash
make # this will compile all the files
make run # this will run all the files
```

If you're not using a make file
```bash
To Compile: gcc -Wall forkexecvp.c 
            gcc -Wall -O -o hw1 hw1.c ### must compile both files 

To Run: ./a.out ./hw1 < number for array indexing  ex:10000 >
```

# My Files

### static void sigint_handler(int sig)
This function handles the SIGINT signal (control c). When SIGINT is received through the terminal the function uses an if else statement to check if a valid child process ID is present and sends SIGTERM to terminate the child process. Since SIGINT traditionally terminates the entire process, SIGTERM must be called to allow the parent process to continue running after the child is terminated. It then prompts the user to use SIGQUIT ( control \ ) to terminate the program. 

### void sigtstp_handler(int sig)
This function handles the SIGSTP signal (control z). It uses a print statement to prompt the user to use SIGQUIT to terminate the program. 

### void sigquit_handler(int sig)
This function handles the SIGQUIT signal ( control \ ). It terminates the entire program, but prints a message to indicate that the quit signal was received first. 

### int main(int argc, char **argv)
The main function of this program begins by ensuring that the user provides the necessary command line arguments for the program to run as intended. Once that is done, it sets signal handlers for SIGINT, SIGSTP and SIGQUIT. Next, fork() is used to create a child process from the original and uses execvp() to execute the given command. 

# Github repo link
https://github.com/blainesea/cs332-532

# References

I used the Lab Workbook and the given files as a starting point for this program. 

I used this article for assistance with understanding SIGINT, SIGTERM and SIGQUIT: 
    https://www.baeldung.com/linux/sigint-and-other-termination-signals