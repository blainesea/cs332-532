#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/* checking to see if input number is prime
will return 1 if yes, 0 if no */
int isPrime(int num) {
    if (num < 2) {
        return 0; /* not a prime number */
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; /* not a prime number */
        }
    }
    return 1; /* is a prime number */
}

/* function to calculate the sum of digits of given number */
int sumOfDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

/* main function for first problem. 
will return a different number / string based on user input 
uses pointers and dynamic memory allocation to return a string in some instances */
char* numberTransformer(int n) {
    if (isPrime(n) && n != 3 && n != 5) {
        return "Go Blazers"; /* prime number other than 3 or 5 */
    } else if ((n & (n - 1)) == 0) {
        /* power of 2: finding the nearest prime below n and return the sum as a string */
        int nearestPrime = n - 1;
        while (!isPrime(nearestPrime)) {
            nearestPrime--;
        }
        int result = n + nearestPrime;
        char* resultString = (char*)malloc(20 * sizeof(char)); /* using malloc to allocate memory for the resultString */
        sprintf(resultString, "%d", result);
        return resultString;
    } else if (n % 3 == 0 && n % 5 == 0) {
        return "UAB CS 332&532"; /* divisible by both 3 and 5 */
    } else if (sumOfDigits(n) % 3 == 0) {
        return "CS"; /* sum of digits is divisible by 3 */
    } else {
        /* default case: return the square of the sum of digits as a string */
        int sumSquared = pow(sumOfDigits(n), 2);
        char* resultString = (char*)malloc(20 * sizeof(char));
        sprintf(resultString, "%d", sumSquared);
        return resultString;
    }
}

/* function for problem 2: checking to see if n2 is a UABNumber 
returning a boolean (true or false)*/
bool UABNumber(int n2) {
    /* storing the sum of divisors */
    int sumOfDivisors = 0;

    /* iterating thru divisors (1 to n2-1) */
    for (int i = 1; i < n2; i++) {
        /* checking if i is a divisor of n2*/
        if (n2 % i == 0) {
            /* adding to sumOfDivisors if i is a divisor*/
            sumOfDivisors += i;
        }
    }

    /* returning true if sumOfDivisors == n2, otherwise return false */
    return (sumOfDivisors == n2);
}

/* function for problem 3: returning the int from user input and 
returning it in reverse */
int reverseNum(int n3) {
    int reversed = 0;
    while (n3 > 0) {
        /* finds last num in n3 by giving remainder when n3 is divided by 10 
        assigns last digit of n3 to be the first digit of 'reversed'*/
        reversed = reversed * 10 + n3 % 10; 
        /* removes last digit of n3 */
        n3 /= 10;
    }
    return reversed;
}
/* function for problem 4: returning how many numbers in the given array 
are smaller than their index */
int smallerThanIndex(int numbers[]) {
    int count = 0;
    /* looping thru each element in the array */
    for (int i = 0; i < 5; i++) {
        /* checking if current value is < its index */
        if (numbers[i] < i) {
            /* add to counter if value is < its index */
            count++;
        }
    }
    return count;
}

/* function for problem 5: 
returning:  1. min value 
            2. min value's index
            3. the mean (rounded to nearest hundredth)
            4. max value
            5. max value's index   */
void arrayDetails(int array[]) {
    /* initialize variables for min, max, sum, and their indices */
    int min = array[0];
    int minIndex = 0;
    int max = array[0];
    int maxIndex = 0;
    double sum = array[0];

/* iterate thru array to find min, max, and calc sum */
    for (int i = 1; i < 6; i++) {
        if (array[i] < min) {
            min = array[i];
            minIndex = i;
        }
        if (array[i] > max) {
            max = array[i];
            maxIndex = i;
        }
        sum += array[i];
    }

    /* calculate mean and round it to the nearest hundredth */
    double mean = sum / 6.0;

    /* printing details array */
    printf("Details Array: [%d, %d, %.2f, %d, %d]\n", min, minIndex, mean, max, maxIndex);
}

/* main function for user input for all functions in this assignment */
int main() {
    /* variable for numberTransformer */
    int number;

    /* variable for UABNumber */
    int n2;

    /* variable for reverseNum */
    int n3;

    /* empty array for smallerThanIndex */
    int numbers[5];

    /* empty array for detailsArray */
    int detailsArray[6]; 
    
    /* user input for numberTransformer */
    printf("Enter a positive integer for numberTransformer: ");
    scanf("%d", &number);

    /* ensuring that for numberTransformer, the user does not provide a negative num */
    if (number > 0) {
        printf("%s\n", numberTransformer(number));
    } else {
        printf("Invalid input. Please enter a positive integer.\n");
    }

    /* Get input from the user for UABNumber */
    printf("Enter an integer for UABNumber: ");
    scanf("%d", &n2);

    /* printing results of UABNumber  */
    if (UABNumber(n2)) {
        printf("TRUE - %d is a UABNumber.\n", n2);
    } else {
        printf("FALSE - %d is not a UABNumber.\n", n2);
    }

    /* Get input from the user for reverseNum */
    printf("Enter a positive integer for reverseNum: ");
    scanf("%d", &n3);

    /* ensuring that for reverseNum, the user does not provide a negative num */ 
    if (n3 > 0) {
        printf("Reversed Number: %d\n", reverseNum(n3));
    } else {
        printf("Invalid input. Please enter a positive integer.\n");
    }

    /* getting input from the user for smallerThanIndex */
    printf("Enter 5 integers for smallerThanIndex. Press ENTER between each number: ");
    /* looping thru array to get all 5 values */
    for (int i = 0; i < 5; i++) {
        scanf("%d", &numbers[i]);
    }

    /* printinf results from smallerThanIndex */
    printf("Number of integers smaller than their index: %d\n", smallerThanIndex(numbers));

    /* getting input from the user for smallerThanIndex */
    printf("Enter 6 integers for arrayDetails. Press ENTER between each number: ");
    for (int i = 0; i < 6; i++) {
        scanf("%d", &detailsArray[i]);
    }

    /* call and print the result of arrayDetails */
    arrayDetails(detailsArray);

    return 0;
}
