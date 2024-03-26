/* 
  Simple Pthread Program to find the sum of a vector - Version 2
  Each thread computes the partial sum, writes the partial sum to 
  a separate global variable and the main thread computes the global sum. 
  Author: Purushotham Bangalore
  Date: Jan 25, 2009

  To Compile: gcc -O -Wall pthread_sum2.c -lpthread
  To Run: ./a.out 1000 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// structure to hold thread data
typedef struct {
    double *a;     // Pointer to the vector
    double sum;    // Partial sum for the thread
    int N;         // Total number of elements
    int size;      // Total number of threads
    long tid;      // Thread ID
} ThreadData;

// Thread function to compute partial sum
void *compute(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int myStart, myEnd, myN, i;

    myN = data->N / data->size;
    myStart = data->tid * myN;
    myEnd = myStart + myN;
    if (data->tid == (data->size - 1)) myEnd = data->N;

    data->sum = 0.0; // Initialize partial sum
    for (i = myStart; i < myEnd; i++)
        data->sum += data->a[i];

    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <# of elements> <# of threads>\n", argv[0]);
        exit(-1);
    }

    int N = atoi(argv[1]);
    int size = atoi(argv[2]);
    double globalSum = 0.0;
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * size);
    ThreadData *threadData = (ThreadData *)malloc(sizeof(ThreadData) * size);
    double *a = (double *)malloc(sizeof(double) * N);

    // Initialize vector
    for (int i = 0; i < N; i++)
        a[i] = (double)(i + 1);

    // Create threads
    for (long i = 0; i < size; i++) {
        threadData[i].a = a;
        threadData[i].N = N;
        threadData[i].size = size;
        threadData[i].tid = i;
        pthread_create(&threads[i], NULL, compute, (void *)&threadData[i]);
    }

    // Wait for threads to complete and aggregate sum
    for (int i = 0; i < size; i++) {
        pthread_join(threads[i], NULL);
        globalSum += threadData[i].sum;
    }

    printf("The total is %g, it should be equal to %g\n", globalSum, ((double)N * (N + 1)) / 2);

    // Clean up
    free(a);
    free(threads);
    free(threadData);

    return 0;
}