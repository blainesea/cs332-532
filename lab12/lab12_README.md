# Compilation Instructions

If you're a make file
```bash
make # this will compile all the files
make run # this will run all the files
```

If you're not using a make file
```bash
To Compile: gcc -o lab12 lab12.c 

To Run: ./lab12
```

# My Files

### main
The entire program is contained within this main function. It begins with a while loop that will execute infinitely (or until the quit command is input through the terminal). Within that loop, it prompts the user for commands, trims away any new line characters that could mess with the output, checks for the quit command, opens the command to be read and then reads it one line at a time and outputs it to the terminal. 


# Github repo link
https://github.com/blainesea/cs332-532

# References

I used the Lab Workbook for help with understanding the concepts of pipes.  

I used this article for assistance with creating the Linux shell.
    https://www.geeksforgeeks.org/making-linux-shell-c/