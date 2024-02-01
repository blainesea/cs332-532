# Compilation Instructions

If you're a make file
```bash
make # this will compile all the files
make run # this will run all the files
```

If you're not using a make file
```bash
gcc Wall -o <executable name> <lab4.c> # this will compile the lab4 file and return an executable with the executable name
```

# My Files

### main()
Everything accomplished in this program is done within the main() function. First variables are declared for file descriptors for both files that the program will be working with. Two other variables are declared to ensure that the correct data is written to the file in the end and for ease of reading (bytesRead and buffer respectively). Next, an 'if' statement is used to check if the user correctly inputs the amount of arguments through the command line. Two more 'if' statements are then used to open and read the given files, where then a for loop will write the contents from the first file into the second file. Lastly, another 'if' statement is used to ensure that the files were read in correctly. Each different 'if' statement in this program contains the functionality to tell the user that there was an error in running the specific portion of the program. If there are no errors, the program will tell the user that the files were concatenated successfully. 

# Github repo link
https://github.com/blainesea/cs332-532

# References

I used the lecture slides from 2/1/24 as well as the filecopy.c given in the Lab Assignment as points of reference for this program. 