# Compilation Instructions

If you're a make file
```bash
make # this will compile all the files
make run # this will run all the files
```

If you're not using a make file
```bash
To Compile: gcc -O -Wall pthread_sum2.c -lpthread 

To Run: ./a.out <num of elements> <number of threads to use>
```

# My Files

### typedef struct     (ThreadData)
This structure holds all necessary data for each thread so that the necessary computations for the program can be accomplished. Variables a and sum are of type double, variables N and size are type int and the thread iD has the type long. 

### void *compute(void *arg)
Each thread in the program uses this function to calculate a portion of the total sum. The function updates the sum within ThreadData to avoid the usage of any global variables like the program had done originally. 

### int main(int argc, char **argv)
The main function of this program needs two command line arguments from the user to execute, the number of elements in an array and the number of threads to use. Memory is then dynamically allocated for those numbers within the struct ThreadData. Threads are then initialized through a for loop that provides it with all necessary information such as the array pointer and thread iD. The function then joins all threads together through pthread_join and adds all partial sums into a new global sum. Lastly, results of the program are printed to the console. 

# Github repo link
https://github.com/blainesea/cs332-532

# References

I used the Lab Workbook and the given files as a starting point for this program. 

I used this article for assistance with understanding the concepts behind multi-threading: 
    https://www.geeksforgeeks.org/multithreading-in-c/