#include <stdio.h>
#include <stdbool.h>

/* Using boolean to determine if number is even or odd */
bool isOddOrEven(int number) {
    return (number % 2 == 0);
}

int main() {
	/* declaring empty var to store user input */
	int given_number;

	/* gathering user input */
	printf("Enter a number: ");
	scanf("%d", &given_number);

	/* printing results */
	if (isOddOrEven(given_number))
		printf("The number is an even number. \n");
	else
		printf("The number is an odd number. \n");

	return 0;
}
