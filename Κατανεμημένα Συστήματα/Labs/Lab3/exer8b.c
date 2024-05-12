#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define LOOP_SIZE 10000000

volatile unsigned long shared_counter = 0;
volatile unsigned int num_threads = 0;

pthread_mutex_t mutex;

void *thread_work(void *arg) {
    long mytid = (long)arg;
    long iterations = LOOP_SIZE / num_threads;
    
    if (mytid == num_threads-1)
        iterations += LOOP_SIZE % num_threads;

    printf("Thread: %ld starts working\n", mytid);

    pthread_mutex_lock(&mutex);   
    for (long i = 0; i < iterations; i++) {
       shared_counter += 1;
    }
    pthread_mutex_unlock(&mutex);

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
    pthread_mutex_init(&mutex, NULL);
    // Create threads
    for (long t = 0; t < num_threads; t++)
        pthread_create(&threads[t], NULL, thread_work, (void *)t);

    for (long t = 0; t < num_threads; t++)
        pthread_join(threads[t], NULL);
    pthread_mutex_destroy(&mutex);
    printf("\nMain thread: shared_counter: %ld\n", shared_counter);
    return 0;
}