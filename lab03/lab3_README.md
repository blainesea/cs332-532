# Compilation Instructions

If you're a make file
```bash
make # this will compile all the files
make run # this will run all the files
```

If you're not using a make file
```bash
gcc -o <executable name> <lab3.c> # this will compile the lab3 file and return an executable with the executable name
```

# My Files

### main()

This function prompts the user to input the number of strings they would like to be sorted, allocates memory for an array of the strings the user will input and then calls to the functions below so that they can be sorted. Lastly, it frees the same memory so that there are no leaks and the program is efficient. 

### void insertionSortStrings(char *arr[], int n)
This function takes in an array of strings (arr) and its size as int (n) that are both declared in the main function. It then initializes variables i and j (both ints) and *key (char) that will be used to store the current element during the sorting process. It then uses a for loop to iterate through the array and a while loop to sort through the sorted portion of the array all while shifting each element of the array into its correct spot. 

### void readStrings(char *arr[], int n)
This function also takes in an array of strings (arr) and its size as int (n) that are both declared in the main function. It then asks the user to enter a number of strings and then a for loop to read in 'n' amount of strings from the user. Scanf then reads in the users strings and stores it within an array where memory is then dynamically allocated for each string. 

### void displaySortedStrings(char *arr[], int n)
Like the functions above, this function takes in an array of strings (arr) and its size as int (n) that are both declared in the main function. This function is used to print each element of the array now that it has been sorted using a for loop that iterates through each element in the array. 

# Github repo link
https://github.com/blainesea/cs332-532

# References

I transferred my code for the insertion sort from my previous lab with a few adjustments to make it work for strings rather than ints. 

I used the TA's example of memory allocation for the array of strings as a blueprint for my code. 

I also used geeksforgeeks.com as an extra reference as to how malloc() works:
https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/