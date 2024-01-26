#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSortStrings(char *arr[], int n);
void readStrings(char *arr[], int n);
void displaySortedStrings(char *arr[], int n);

int main() {
    int n;

    /* prompting user to enter the number of strings in the array */
    printf("Enter the number of strings: ");
    scanf("%d", &n);

    /* allocating memory for an array of strings */
    char **arr = (char **)malloc(n * sizeof(char *));

    /* calling readStrings function to read the strings from the user */
    readStrings(arr, n);

    /* calling insertionSortStrings function to sort the strings */
    insertionSortStrings(arr, n);

    /* displaying the sorted strings */
    printf("Sorted strings: ");
    displaySortedStrings(arr, n);

    /* free allocated memory */
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

/* copied insertionSort from my previous lab, included changes to make the input the 
pointer to arr[] rather than the array itself for dynamic memory allocation */
void insertionSortStrings(char *arr[], int n) {
    int i, j;
    char *key;
    /* setting up structure for insertion sort so that arr(i) is compared with the 
    sorted portion of the array */
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* moving elements of array that are > than key to correct position */
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/* reading strings that the user inputs and allocating memory 
for each string */
void readStrings(char *arr[], int n) {
    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Enter string %d: ", i + 1);

        /* dynamically allocating memory for each string 
        used example code from lab to help make these lines */
        arr[i] = (char *)malloc(n * sizeof(char)); 
        scanf("%s", arr[i]);
    }
}

/* function to display each string in alphabetical order */
void displaySortedStrings(char *arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}
