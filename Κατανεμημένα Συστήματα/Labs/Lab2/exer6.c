#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000

volatile float A[ARRAY_SIZE];
volatile float B[1][ARRAY_SIZE];
volatile float C[ARRAY_SIZE] = {0.0};
volatile unsigned int num_threads;

void *thread_work(void *arg) {
    long mytid = (long)arg;
    long sum = 0;

    int chunk_size = ARRAY_SIZE / num_threads;
    int start = mytid * chunk_size;
    int end = (mytid + 1) * chunk_size;
    if (mytid == num_threads - 1) {
        // Adjust the end of the last thread to cover any remaining elements
        end = ARRAY_SIZE;
    }
    for (int i = start; i < end; ++i)
        C[i] = A[i] * B[1][i];
    printf("Thread: %ld -- Reads array: start: %d - end: %d\n", mytid, start, end - 1);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return EXIT_FAILURE;
    }
    num_threads = atoi(argv[1]);
    if (num_threads <= 0) {
        printf("Number of threads must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    for (long i = 0; i < ARRAY_SIZE; i++) {
        A[i] = i + 1.0;
		B[1][i] = 1.0/(i + 1);
	}
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    // Create threads
    for (long t = 0; t < num_threads; t++)
        pthread_create(&threads[t], NULL, thread_work, (void *)t);
    printf("This is the main thread\n");
    for (long t = 0; t < num_threads; t++)
        pthread_join(threads[t], NULL);
	for (long i = 0; i < ARRAY_SIZE; i++)
		printf("C[%ld] = %.2lf \t", i, C[i]);
	printf("\n");
    return 0;
}