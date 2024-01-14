# Compilation Instructions

If you're using a make file:
```bash
make # this will compile all the files
make run # this will run all the files

```

If you're not using a make file:
```bash
gcc -o <executable name> <filename> # this will compile the filename and return an executable with the executable name

```

# My Files
## isOddOrEven.c

### main()

This function begins by declaring the int given_number and then uses printf and scanf to ask the user to input a number and then take that number and store it inside given_number. It then uses an if else statement to print the correct output  

### bool isOddOrEven(int number)
This function returns a boolean

This function takes an integer as a parameter

It checks to see if the int parameter is even by seeing if it can be divided by two with no remainder. The function will return true if "number" is even or false if "number" is odd. 

# GitHub Link
https://github.com/blainesea/cs332-532

# References

I used the palindrome.c file given in the lab assignment as a frame of reference as to how I could format this program. 

I used the example README file from the lab assignment as an outline to create this README file.