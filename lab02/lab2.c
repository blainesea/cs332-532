#include <stdio.h>

void insertionSort(int arr[], int n) {
    int i, key, j;
    /* setting up structure for insertion sort so that arr(i) is compared with the 
    sorted portion of the array */
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* moving elements of array that are > than key to correct position */ 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    /* initializing array w/ 10 elements and n so that the for loop below 
    only prompts the user for 10 input numbers */
    int arr[10];
    int n = 10;

    /* prompting user to enter ten numbers for array*/
    printf("Enter 10 array elements:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    /* calling to insertionSort function from above*/
    insertionSort(arr, n);

    /* printing the sorted array */
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
