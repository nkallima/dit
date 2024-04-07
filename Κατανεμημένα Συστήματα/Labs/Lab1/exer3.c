#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000

volatile int shared_array[ARRAY_SIZE];
volatile unsigned int num_threads;

void *thread_work(void *arg) {
    long mytid = (long)arg;

    int chunk_size = ARRAY_SIZE / num_threads;
    int start = mytid * chunk_size;
    int end = (mytid + 1) * chunk_size;
    if (mytid == num_threads - 1) {
        // Adjust the end of the last thread to cover any remaining elements
        end = ARRAY_SIZE;
    }
    printf("Thread: %ld -- Initiliazes array: start: %d - end: %d\n", mytid, start, end - 1);
    for (int i = start; i < end; ++i)
        shared_array[i] = i * i; // Initialize each element with its index squared
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

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    // Create threads
    for (long t = 0; t < num_threads; t++)
        pthread_create(&threads[t], NULL, thread_work, (void *)t);
    printf("This is the main thread\n");
    for (long t = 0; t < num_threads; t++)
        pthread_join(threads[t], NULL);
    return 0;
}