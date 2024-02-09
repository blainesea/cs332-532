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
```

# My Files

### void printDetailsDefault(const char *filename, const struct stat *info)
This function takes in a pointer that represents the file name and a structure that contains information about the files. It then uses a print statement to print the files name, its size in bytes, number of permissions, and the date and time that the file was last accessed.

### int matchCriteria(const char *filename, const struct stat *info, off_t sizeLimit, const char *pattern, int depthLimit)
This function is used to determine whether the given file meets the criteria given in the command line for the -L and -s prompts. It uses two if statements to ensure that the given file meets the criteria given in the command line. The first "if" checks to see if the file size is > 0 and if it exceeds the givn size limit. The second "if" checks to see if the pattern given is within the file name. If both requirements are true, the function returns 1, otherwise it will return 0. 

### void printDirectory(const char *dirname, int depth, int showDetails, off_t sizeLimit, const char *pattern, int depthLimit, PrintDetailsFunction printDetails)
This function traverses the file directory and prints all files within it recursively. First, it opens the directory provided by the user (if that directory cannot be found an error message will be returned) and prints the name of the directory and the files within it with the correct indentation using a for loop. An if statement is used next to see if the user requested that the files details be printed as well using the "-v" command. Then, a while loop is used to traverse all directories and files. If statements are used within the while loop to recursively print all files within the directory and any symbolic links if they are present. 

### void search(const char *dirname, int depth, int showDetails, off_t sizeLimit, const char *pattern, int depthLimit)
This function is used to initiate the traversal and printing processes by encapsulating the parameters for traversal and passes them to the printDirectory function. 

### int main(int argc, char *argv[])
This is the main function of the program. It uses getopt() to begin the directory traversal and a while loop that contains switch/case options to provide the user with the details of the file if -v is selected, all files in the hierarchy with a file size greater than or equal to the value specified by the user when -L is selected and all files that contain a given string in their name and depth of the file relative to the starting directory when -s is selected. An error handling case is also included along with an if statement that sets the directory name. Finally, the function initiates the search function explained above with the correct parameters. 

# Github repo link
https://github.com/blainesea/cs332-532

# References

I used geeksforgeeks as clarification for the getopt() function and their switch case example: 
https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/

I used ChatGPT to help explain the functions in this readme file because I began working on this last week and forgot some of what I did :)
    I copied snippets of my code and asked ChatGPT to explain it to me. I then put its explanation into my own words. 