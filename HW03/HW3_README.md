# Compilation Instructions

If you're a make file
```bash
make # this will compile all the files
make run # this will run all the files
```

If you're not using a make file
```bash
gcc -o <executable name> <search.c> # this will compile the lab3 file and return an executable with the executable name

./ <executable name> . # prints file hierarchy of current directory 

./ <executable name> -v # prints file hierarchy with more details 

./ <executable name> -L < file size in bytes > # prints files in hierarchy with size >= file size given 

./ <executable name> -s <string pattern> <depth> # prints files in hierarchy that contains the string pattern in the file name AND the depth of the file compared to the starting directory 

./ <executable name> -e <unix-command with arguments> # For each file that matches the search criteria the UNIX command specified with arguments will be executed. 
```

# My Files

### void doChecks(struct command c, checkFlags *f)
This function performs checks for command line flags by calling checkFlags on the command structure. 

### void getV(Command c)
Checks for the "-v" command line flag. If found, it will print detailed information about each file in the given directory. 

### void getL(Command c)
Checks for the "-L" command line flag along with a size limit in bytes. If found, the maximum file size limit will be stored in the command structure. 

### void getS(Command c)
Checks for the "-s" command line flag. This flag allows the user to search by a string pattern as well as file depth limit. The function stores those values in the Command structure. 

### void getS(Command c)
Checks for the "-t" command line flag. This flag allows the user to search by file type, which is then stored in the Command structure. 

### void getE(Command c)
Checks for the "-e" command line flag. This flag allows the user to execute any UNIX command on each file in the given directory. The command that will be executed is stored in the Command structure. 

### void *print_permissions(mode_t mode, char *retPerms)
This function creates a string representation of the file permissions that are enabled and copies it to 'retPerms'. 

### char *getSymLink(struct stat s, char *path)
Checks if a given file is a symbolic link and finds where it links to. The symbolic link's target is returned as 'linkTo'.

### char *getDetails(struct stat s, char *path, char *details)
This function returns all details required by the "-v" flag in a detailed string. Information included: name, size, permissions and latest access time. 

### void choosePrint(struct stat s, char *currentPath, char *details, int det)
This function chooses the correct printing format depending on if a file is a symbolic link or verbose mode (-v) is enabled or neither. The file details will be printed accordingly. 

### void executeCommandOnFile(const char *filePath, const char *baseCommand)
This function enables the user to use any UNIX command along with the '-e' flag on the given directory. 

### void search(char *path, int indent, Command c)
This function traverses the given directory and prints the details of the files within it based on what command line arguments the user inputs. 

### int main(int argc, char **argv)
The main function of the program initializes the Command structure where all command line arguments are stored, parses through the command line arguments and calls to the search function to begin traversing through the given directory. 

# Github repo link
https://github.com/blainesea/cs332-532

# References

I used the HW2 answer file provided in Canvas as a starting point for this assignment. 
    References used within that file apply to this as well. 

I used ChatGPT to help explain the original HW2 file and with making this README file
    I copied the original code into ChatGPT and asked it to explain each function so that I could better understand it before working with it. 

I used SheCodes.io for help with understanding how to interpret the UNIX commands in C. 
    https://www.shecodes.io/athena/68870-how-to-write-a-unix-command-line-interpreter-in-c

I used stackoverflow for help with fork/exec/wait 
    https://stackoverflow.com/questions/19099663/how-to-correctly-use-fork-exec-wait

