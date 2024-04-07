#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000

volatile int shared_array[ARRAY_SIZE];
volatile unsigned int num_threads;
volatile long *sums;

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
        sum += shared_array[i];
    printf("Thread: %ld -- Reads array: start: %d - end: %d - sum: %ld\n", mytid, start, end - 1, sum);
	sums[mytid] = sum;
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

    for (long i = 0; i < ARRAY_SIZE; i++)
        shared_array[i] = i*i;

	sums = calloc(num_threads, sizeof(long));
	for (long i = 0; i < num_threads; i++)
		sums[i] = 0;
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    // Create threads
    for (long t = 0; t < num_threads; t++)
        pthread_create(&threads[t], NULL, thread_work, (void *)t);
    printf("This is the main thread\n");
    for (long t = 0; t < num_threads; t++)
        pthread_join(threads[t], NULL);
	
	long sum = 0;
	for (long t = 0; t < num_threads; t++)
		sum += sums[t];
	printf("The average value is: %ld\n", sum/ARRAY_SIZE);
    
	return 0;
}