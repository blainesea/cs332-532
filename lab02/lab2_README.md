# Compilation Instructions

If you're a make file
```bash
make # this will compile all the files
make run # this will run all the files
```

If you're not using a make file
```bash
gcc -o <executable name> <lab2.c> # this will compile the lab2 file and return an executable with the executable name
```

# My Files
## gettime.c

### main()

This function initializes an array with ten elements and then prompts the user 
to input ten numbers to place inside of that array. A for loop is used to place each number into the array, calls the insertionSort() function to sort it, and then utilizes a print statement and another for loop to output the sorted array. 

### void insertionSort(int arr[], int n)
This function takes in an array of integers (arr) and an int (n) that are both declared in the main function. It then initializes variables i, key and j (all ints) that are used in a for loop and while loop that set up the structure to use insertion sort to sort the array and move each element into its correct place within the sorted portion of the array respectively. 

# Github repo link
https://github.com/blainesea/cs332-532

# References


While I did not directly copy from a previous assignment, I have coded many sorting algorithms in my previous cs330 course including insertion sort, so knowledge from that class was used to make this algorithm. 