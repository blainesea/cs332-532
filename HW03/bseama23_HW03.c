// Include all needed libraries
#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>


// Macros defined for usage across the entire file
// Defining indices for specific flags so that it is clear across the file
#define vIndex 0
#define lIndex 1
#define sIndex 2
#define s2Index 3
#define tIndex 4
#define eIndex 5

// Defining total number of flags, change this to add more flags
#define numFlags 6

// Temporary sizes for paths or just small strings
#define PATH_SIZE 1024
#define TEMP_SIZE 25

// Struct to hold basic information to easily pass data to different functions
struct command
{
	// Holds all arguments starting from index 1 of argv from main
	char **argv;
	// Holds just the arguments from each flag
	char **flagArgs;
	// Holds the starting path and updated paths
	char *path;
    //new field for -e 
    char *execCommand; 
	// Holds number of command line arguments without the executable ex. "./search"
	int argc;
};

// Allows for "Command" type
typedef struct command Command;

// Allows for checkFlags function call type
typedef void checkFlags(Command c);

// Calls a checkFlags type function to be called
void doChecks(struct command c, checkFlags *f)
{
	f(c);
}

// Function to go through the arguments and find -v if it exists.
void getV(Command c)
{
	// For loop for arguments
	for (int i = 0; i < c.argc; i++)
	{
		// Check if any argument is equivalent to -v
		if (strstr(c.argv[i], "-v") != NULL)
		{
			// Placeholder in array so that you know v was found when checking flagArgs
			char *temp = "-v is active!";
			// Allocate space in array
			int length = strlen(temp);
			c.flagArgs[vIndex] = (char *)malloc(length * sizeof(char));
			// Copy placeholder to array
			strcpy(c.flagArgs[vIndex], temp);
		}
	}
}

// Function to go through the arguments and find -L if it exists.
void getL(Command c)
{
	// Loop through all of the arguments
	for (int i = 0; i < c.argc; i++)
	{
		// If any argument equals "-L" we will try to get the argument
		if (strstr(c.argv[i], "-L") != NULL)
		{
			// If there are no more arguments afterwards or the next argument is another flag we error out
			if (c.argc <= i + 1 || c.argv[i + 1][0] == '-')
			{
				printf("INVALID ARGUMENT SYNTAX; Expecting '-L <max file size>'\n");
				exit(-1);
			}

			// Otherwise copy the argument into the flagArgs array
			else
			{
				char *temp = c.argv[i + 1];
				c.flagArgs[lIndex] = (char *)malloc(strlen(temp) * sizeof(char));
				strcpy(c.flagArgs[lIndex], temp);
			}
		}
	}
}

// Function to go through the arguments and find -v if it exists.
void getS(Command c)
{
	// Loop through the array
	for (int i = 0; i < c.argc; i++)
	{
		// If any argument equals "-s" we will try to get the argument
		if (strcmp(c.argv[i], "-s") == 0)
		{
			// If there is no more arguments after 2 arguments or either of the next 2 arguments is another flag we error out
			if (c.argc < i + 2 || c.argv[i + 2][0] == '-')
			{
				printf("INVALID ARGUMENT SYNTAX; Expecting '-s <string pattern> <depth>'\n");
				exit(-1);
			}
			// Otherwise get the next two arguments and
			else
			{
				// Allocate space and copy arguments to flagArgs array
				char *temp = c.argv[i + 1];
				int len = strlen(temp);
				c.flagArgs[sIndex] = (char *)malloc(len * sizeof(char));
				strcpy(c.flagArgs[sIndex], temp);

				temp = c.argv[i + 2];
				len = strlen(temp);
				c.flagArgs[s2Index] = (char *)malloc(len * sizeof(char));
				strcpy(c.flagArgs[s2Index], temp);
			}
		}
	}
}

// Function to go through the arguments and find -v if it exists.
void getT(Command c)
{
	// Loop through the array
	for (int i = 0; i < c.argc; i++)
	{
		// If any argument equals "-t" we will try to get the argument
		if (strstr(c.argv[i], "-t") != NULL)
		{
			// If there isn't at least 1 more argument after the -t or the next argument isn't "f" or "d", error and exit
			if ((c.argc <= i + 1) || (strstr(c.argv[i + 1], "f") == NULL && strstr(c.argv[i + 1], "d") == NULL))
			{
				printf("INVALID ARGUMENT SYNTAX; Expecting '-t <file type (f,d)>'\n");
				exit(-1);
			}
			// Otherwise allocate space and copy argument over to flagArgs
			else
			{
				char *temp = c.argv[i + 1];
				c.flagArgs[tIndex] = (char *)malloc(sizeof(char));
				strcpy(c.flagArgs[tIndex], temp);
			}
		}
	}
}
void getE(Command *c) // Modified to accept Command pointer
{
    for (int i = 0; i < c->argc; i++)
    {
        if (strcmp(c->argv[i], "-e") == 0)
        {
            if (i + 1 < c->argc)
            {
                c->execCommand = strdup(c->argv[i + 1]);
                break;
            }
            else
            {
                printf("ERROR: -e option requires a command to execute.\n");
                exit(-1);
            }
        }
    }
}
// CHATGPT: https://chat.openai.com/share/682356e5-89dc-4117-b5c7-aaa82bdd52d2
void *print_permissions(mode_t mode, char *retPerms)
{
	// String that will be manipulated to hold the permissions for the file provided
	char perms[10] = "---------";
	// All possible permission types
	mode_t flags[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	// String version of having all permissions enabled
	char perm_chars[10] = "rwxrwxrwx";
	// Loop through the number of flags and check the bit with a bitwise AND operation
	for (int i = 0; i < 9; ++i)
	{
		if (mode & flags[i])
		{
			perms[i] = perm_chars[i];
		}
	}

	// Copy to a pointer from calling function
	strcpy(retPerms, perms);
}

// References: https://man7.org/linux/man-pages/man2/readlink.2.html
// Function to find symbolic links and where they link to
char *getSymLink(struct stat s, char *path)
{
	// Initialize and declare link name string
	char *linkTo = (char *)malloc(PATH_SIZE * sizeof(char));

	// Check if the file/directory is a symbolic link
	if (S_ISLNK(s.st_mode))
	{
		// If the file is a symbolic link, call readlink and get the original source's name
		ssize_t len = readlink(path, linkTo, s.st_size + 1);
		// Error case
		if (len == -1)
		{
			perror("readlink");
			free(linkTo);
		}
	}
	// Return the original source's name
	return linkTo;
}

// Function to get all the details that the verbose flag requires
// Adds everything into one string to return
char *getDetails(struct stat s, char *path, char *details) {
    char *fileName = strrchr(path, '/');
    if (!fileName) {
        fileName = path; // If no '/' found, the path itself is the file name
    } else {
        fileName++; // Move past the last '/'
    }

    details = (char *)malloc(PATH_SIZE * sizeof(char));

    long bytes = S_ISDIR(s.st_mode) ? 0 : s.st_size;

    char perms[10];
    print_permissions(s.st_mode, perms); // Assuming this function fills perms correctly

    time_t at = s.st_atime;
    char *accessTime = ctime(&at);
    accessTime[strlen(accessTime) - 1] = '\0'; // Remove newline

    // Include the file name in the details string
    sprintf(details, "%s | %ld | %s | %s", fileName, bytes, perms, accessTime);

    return details;
}


// Function to choose different printing options
void choosePrint(struct stat s, char *currentPath, char *details, int det)
{
	// Create linkTo variable for easy access to free
	char *linkTo = NULL;

	// Initialize symbolic link to false
	int sym = 0;

	// If it is a symbolic link, linkTo will have the link's name and sym will be updated to true
	if (S_ISLNK(s.st_mode))
	{
		linkTo = getSymLink(s, currentPath);
		sym = 1;
	}

	// Get name of the current file
	char *lastBack = strrchr(currentPath, '/');
	char *lastDir = &lastBack[1];

	// If the file is a symbolic link and -v is enabled
	if (sym && det)
	{
		printf("%s (%s) %s\n", lastDir, linkTo, details);
	}
	// If the file is a symbolic link
	else if (sym)
	{
		printf("%s (%s)\n", lastDir, linkTo);
	}
	// If the -v is enabled
	else if (det)
	{
		printf("%s %s\n", lastDir, details);
	}
	// If none of the above were true, just the name
	else
	{
		printf("%s\n", lastDir);
	}
}

void executeCommandOnFile(const char *filePath, const char *baseCommand) {
    if (baseCommand == NULL || filePath == NULL) return; // Ensure both command and filePath are provided

    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        // Assuming the command requires the file path as the last argument
        // Note: This example assumes the command and its arguments are separated by spaces and does not contain special characters (like quotes)
        char *cmdArgs[64];
        int argCount = 0;

        // Tokenize the command string
        char *tempCommand = strdup(baseCommand); // Duplicate the command to avoid modifying the original string
        char *piece = strtok(tempCommand, " ");
        while (piece != NULL && argCount < 63) {
            cmdArgs[argCount++] = piece;
            piece = strtok(NULL, " ");
        }
        cmdArgs[argCount] = strdup(filePath); // Add the file path as the last argument
        cmdArgs[argCount + 1] = NULL; // NULL-terminate the argument list

        // Execute the command
        if (execvp(cmdArgs[0], cmdArgs) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }

        free(tempCommand); // Cleanup
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the child process to complete

        if (WIFEXITED(status)) {
            int exitStatus = WEXITSTATUS(status);
            //printf("Child exited with status %d\n", exitStatus);
        } else if (WIFSIGNALED(status)) {
            printf("Child killed by signal %d\n", WTERMSIG(status));
        }
    }
}

// Recursive file traversal function
// Takes a intial path, indent of 0, array of arguments for each flag that was enabled
void search(char *path, int indent, Command c) {
    struct dirent *dirent;
    DIR *parentDir = opendir(path);
    if (parentDir == NULL) {
        printf("Error opening directory: '%s'\n", path);
        exit(-1);
    }

    while ((dirent = readdir(parentDir)) != NULL) {
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) continue;

        char *currentPath = (char *)malloc(PATH_SIZE * sizeof(char));
        snprintf(currentPath, PATH_SIZE, "%s/%s", path, dirent->d_name);

        struct stat s;
        if (lstat(currentPath, &s) == -1) {
            perror("lstat");
            free(currentPath);
            continue;
        }

        // Execute command or get details based on flags
        char *details = NULL;
        if (c.flagArgs[vIndex] != NULL || c.execCommand != NULL) {
            details = getDetails(s, currentPath, NULL); // Generate details for every file/directory
        }

        long sizeLimit = (c.flagArgs[lIndex] != NULL) ? atol(c.flagArgs[lIndex]) : LONG_MAX;
        if (s.st_size < sizeLimit && c.flagArgs[lIndex] != NULL) {
            free(details);
            free(currentPath);
            continue; // Skip files smaller than the limit specified by -L
        }

        // Check for -s flag conditions
        if (c.flagArgs[sIndex] != NULL && strstr(dirent->d_name, c.flagArgs[sIndex]) == NULL) {
            free(details);
            free(currentPath);
            continue; // Skip files not matching the search pattern
        }

        if (c.flagArgs[vIndex] != NULL) {
            // Print details if -v is active
            printf("%*s%s\n", indent * 2, "", details);
        } else {
            // Just print the name if -v is not specified
            printf("%*s%s\n", indent * 2, "", dirent->d_name);
        }

        // If -e option is specified, execute the command on the file
        if (c.execCommand != NULL) {
            executeCommandOnFile(currentPath, c.execCommand);
        }

        free(details);

        // Recursive search in directories, excluding symlink directories to prevent infinite loops
        if (S_ISDIR(s.st_mode) && !S_ISLNK(s.st_mode)) {
            search(currentPath, indent + 1, c);
        }

        free(currentPath);
    }

    closedir(parentDir);
}

int main(int argc, char **argv)
{
	// Initialize setup variables
	int indent = 0;
	//int numArguments = 5;

	// Partial argv array, excludes executable
	char **modArgv = &argv[1];

	// Array of strings or array of array of characters for flags
	char **flagArgs = (char **)malloc(numFlags * sizeof(char *));

	// Initialize struct object with initial values
	Command currentCommand;
	currentCommand.path = NULL;
	currentCommand.argv = modArgv;
	currentCommand.argc = argc - 1;
	currentCommand.flagArgs = flagArgs;
    currentCommand.execCommand = NULL;

	// Flag argument array declaration and malloc initialization
	for (int i = 0; i < numFlags; i++)
	{
		flagArgs[i] = NULL;
	}

	// Function call to find and get any arguments for the possible flags
	doChecks(currentCommand, getV);
	doChecks(currentCommand, getL);
	doChecks(currentCommand, getS);
	doChecks(currentCommand, getT);
    getE(&currentCommand);

	// for (int i = 0; i < numArguments; i++)
	// {
	// 	printf("Flag Arg: %s\n", flagArgs[i]);
	// }

	// If  the executable is the only argument, the path is the current directory and we move on
	if (argc == 1)
	{
		currentCommand.path = (char *)malloc(PATH_SIZE * sizeof(char));
		getcwd(currentCommand.path, PATH_SIZE);
	}
	// Otherwise we have to find the path
	else
	{
		// For loop to go through the arguments excluding the executable
		for (int i = 0; i < currentCommand.argc; i++)
		{
			// If any of the indices of the arguments contain "/", ".", or "..", there is a path to copy
			if (i != s2Index && (strstr(currentCommand.argv[i], "/") != NULL) && (strstr(currentCommand.argv[i], "..") != NULL) || (strstr(currentCommand.argv[i], ".") != NULL))
			{
				// If the provided path start with ".."
				if (strstr(currentCommand.argv[i], "..") != NULL)
				{
					// Allocate memory for the path and get the path using getcwd()
					currentCommand.path = (char *)malloc(PATH_SIZE * sizeof(char));
					char *tempPath = (char *)malloc(PATH_SIZE * sizeof(char));
					getcwd(tempPath, PATH_SIZE);

					// Remove the last folder as "../" insinuates the previous directory
					char *lastBack = strrchr(tempPath, '/');

					// Last back is a pointer to the actual location in the string where the last "/" occurs
					// This makes that location and anything after it '\0'
					if (lastBack != NULL)
					{
						*lastBack = '\0';
					}

					// If the path is exactly ".."
					if (strcmp(currentCommand.argv[i], "../") == 0)
					{
						strcpy(currentCommand.path, tempPath);
					}
					// If the path is partially "../"
					else if (strstr(currentCommand.argv[i], "../") != NULL)
					{
						// Ignore the dots
						*currentCommand.argv[i]++;
						*currentCommand.argv[i]++;
						// Copy and append the path
						strcpy(currentCommand.path, tempPath);
						strcat(currentCommand.path, currentCommand.argv[i]);
					}
					break;
				}
				// Otherwise assume that it is an absolute or local relative path
				else
				{
					currentCommand.path = (char *)malloc(PATH_SIZE * sizeof(char));
					strcpy(currentCommand.path, currentCommand.argv[i]);
				}
			}
		}
		// If the path is still NULL after all of this the current directory gets printed out with an error message
		if (currentCommand.path == NULL)
		{
			printf("Printing from current directory\n");
			currentCommand.path = (char *)malloc(PATH_SIZE * sizeof(char));
			getcwd(currentCommand.path, PATH_SIZE);
		}
	}

	// Removing additional backslash at the end if there is one
	int pathLen = strlen(currentCommand.path);
	if (currentCommand.path[pathLen - 1] == '/')
	{
		currentCommand.path[pathLen - 1] = '\0';
	}

	// Get the last directory's name and print it
	char *lastBack = strrchr(currentCommand.path, '/');
	char *baseDir = &lastBack[1];
	printf("%s\n", baseDir);
	indent++;

	// Call the recursive function to go through the directories
	search(currentCommand.path, indent, currentCommand);

    if (currentCommand.execCommand) free(currentCommand.execCommand); // Clean up execCommand

	// Free up allocated memory
	for (int i = 0; i < numFlags; i++)
	{
		free(currentCommand.flagArgs[i]);
	}

	free(flagArgs);
    free(currentCommand.path);

	// Return from the main
	return 0;
}