# Compilation Instructions

If you're a make file
```bash
make # this will compile all the files
make run # this will run all the files
```

If you're not using a make file
```bash
gcc -o <executable name> <readdir.c> # this will compile the lab4 file and return an executable with the executable name

./<executable name> . # this will print all files in the current directory recursively
```

# My Files

### int main (int argc, char **argv)
This function is the main function of the readdir program. It begins by using an if statement to ensure that the user provides the correct amount of arguments through the command line when running this program. It then initializes a count variable to store the number of files and directories found, prints a message to the user showing that the program is executing correctly, and then calls to listFilesRecursively to do the rest of the work for this program. 

### void listFilesRecursively(char *basePath, int *count)
The purpose of this function is to recursively list all files in a given directory. First, code from the assignment page in canvas was used to open the current directory, and then traverse through all files within the directory, while avoiding anything named "." and ".." because I was encountering infinite loops. It then prints each file along with its index by concatenating basePath with the file's name. Finally, the function uses an if statement to recursively call to itself if another directory is found during traversal, and the directory then closes. 


# Github repo link
https://github.com/blainesea/cs332-532

# References

I used the files provided in Canvas as a starting point for this assignment. 