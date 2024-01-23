# Compilation Instructions

If you're a make file
```bash
make # this will compile the file
make run # this will run the file
```

If you're not using a make file
```bash
gcc -o <executable name> <bseama23_HW01.c -lm > # this will compile the file and return an executable with the executable name

# MUST include -lm so that the pow function inside numberTransformer compiles correctly 
```

# My Files
## bseama23_HW01.c

### int isPrime(int num)
This function checks to see if "num" is a prime number. If it is, the function will return 1, otherwise, it will return 0. This is used within the numberTransformer function to determine if n is prime, where it would then return "Go Blazers" if num is not 3 or 5. 

### int sumOfDigits(int num)
This function calculates the sum of the digits of a given number. This function is used within the numberTransformer function to print "CS" if the sum of the digits is divisible by three, as well as in the default case to return the square of the sum of the digits. 

### char* numberTransformer(int n)
This function takes a number "n" and prints a different response based on that number. It uses multiple if and else if statements to check for the different conditions provided in the assignment. It uses pointers and utilizes malloc for dynamic memory allocation to return a string in some instances. It also uses the math library to find the square of an int using "pow". 

### bool UABNumber(int n2)
This function takes in an int (n2) and determines if that number is a UABNumber (equal to the sum of its positive divisors). It creates an empty variable called sumOfDivisors and uses a for loop and if statement to add to that variable if "i" is a divisor of n2. If sumOfDivisors == n2 at the end of the function, "true" will be returned, otherwise, the function will return "false".

### int reverseNum(int n3)
This function takes an int (n3) and returns that same number but in reverse order. This is accomplished by instantiating an empty variable 'reversed' and using a while loop that finds the last number in 'n3' and assigns that to be the first number in 'reversed' by dividing the entire integer by 10 and giving the remainder using %. Lastly, 'n3' is divided by 10 to effectively remove the last digit from 'n3' and the process is repeated until nothing remains within 'n3' and the reversed number is returned. 

### int smallerThanIndex(int numbers[])
This function takes an array of ints 'numbers[]' and returns the count of how many integers are less than their index inside of the array. First, an empty variable 'count' is initialized to hold the number of integers that are less than their index. This count is increased using a for loop that iterates through each number in the array and checking its value compared to its index, if it is less than the index, 'count' is increased by one, otherwise, it moves on to the next number in the array until there are no values remaining. The correct count is then returned. 

### void arrayDetails(int array[])
This function takes an array of ints 'array[]' and returns 
            1. the array's min value 
            2. the min value's index
            3. the mean of the array (rounded to nearest hundredth)
            4. the array's max value
            5. the max value's index
This is accomplished by initiliazing empty variables to eventually hold each of those 5 values. For loops and if statements are then used to iterate through the array, checking each value and assigning it to min if it is the smallest number within the array (same process for max). The 'sum' variable is incremented as this process happens by adding each value in the array to 'sum' as it is parsed through. Next, the mean is calculated by dividing the sum by 6, since there will always be 6 values inside the given array. Once that is done, each detail for the array is printed in the correct order from above. 

### main()
This function instantiates variables, takes user input and provides the necessary information to each function in the program so that the correct output may be printed to the users screen. 


# Github repo link
https://github.com/blainesea/cs332-532

# References

I used the user inputs and C functions resources provided in the Assignment page (linked below) as well as some code from my cs303 course last semester for help with the numberTransformer function and reverseNum. I originally coded them in Python for that class, but converted it to C for this assigment and made necessary adjustments along the way. 

User inputs: 
https://www.w3schools.com/c/c_user_input.phpLinks to an external site.

C functions: 
https://www.w3schools.com/c/c_functions.phpLinks to an external site.