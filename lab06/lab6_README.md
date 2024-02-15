# Compilation Instructions

If you're a make file
```bash
make # this will compile all the files
make run # this will run all the files
```

If you're not using a make file
```bash
gcc -o <executable name> <lab6.c> # this will compile the lab4 file and return an executable with the executable name

./<executable name> . # this will print all files in the current directory recursively
```

# My Files

### struct listing getfields(char* line)
This is a function that takes in each line of the listings.csv file, parses through it and then puts each field into the structure made above using strtok and ',' as the delimeter as the file is comma seperated. It returns the struct with all the parsed data. This function as well as the creation of the struct was copied from the lab workbook. 

### int compareByName(const void *a, const void *b)
This function is used to to sort the array of elements within the listing struct so that they can be in alphabetical order by the host name. It takes in pointers to the elements being compared 'a' and 'b'. The function will return a negative number if item 1 (a) comes before item 2 (b), a zero if they are equal to each other and a positive if item 1 comes after item 2. This function is then used with qsort later in the program to sort every entry by the name of the host. 

### int compareByPrice(const void *a, const void *b)
This function is nearly exactly the same as the one above, with the only differences being that it helps to sort the array by the price inside the listing struct and it uses an if else statement to return the -1, 0 or 1 based on the values of the items. 

### int main()
The main function contains all the file operations for the program. It starts by declaring a function pointer and other variables that manage memory allocation, and then opens the listings.csv file in read mode so that each line of the file can be read in using fgets() and doubles the allocated memory as needed to avoid segmentation faults. It then calls to getFields() to put each line of the file into the struct and qsort() to sort the array of list items into a new csv file for sorting by host name. The process is repeated for a new file where entries are sorted by price. Memory is then deallocated and a success message is printed when all operations are complete. 

# Github repo link
https://github.com/blainesea/cs332-532

# References

I used the Lab Workbook for the creation of the struct and the function to parse through each line of it. 

I used this article from geekstogeeks for assistance with some segmentation fault errors that I was running into: 
    https://www.geeksforgeeks.org/segmentation-fault-c-cpp/