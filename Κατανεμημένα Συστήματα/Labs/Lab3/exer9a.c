#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOOP_SIZE 10000000

int64_t getTimeMillis(void);

volatile unsigned long shared_counter = 0;
volatile unsigned int num_threads = 0;

pthread_mutex_t mutex;

int64_t getTimeMillis(void) {
    struct timespec tm;

    if (clock_gettime(CLOCK_MONOTONIC, &tm) == -1) {
        perror("clock_gettime");
        return 0;
    } else return tm.tv_sec*1000LL + tm.tv_nsec/1000000LL;
}

void *thread_work(void *arg) {
    long mytid = (long)arg;
    long iterations = LOOP_SIZE / num_threads;
    
    if (mytid == num_threads-1)
        iterations += LOOP_SIZE % num_threads;

    printf("Thread: %ld starts working\n", mytid);
    
    for (long i = 0; i < iterations; i++) {
       pthread_mutex_lock(&mutex);
       shared_counter += 1;
       pthread_mutex_unlock(&mutex);
    }

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

    int64_t start = getTimeMillis();
    // Create threads
    for (long t = 0; t < num_threads; t++)
        pthread_create(&threads[t], NULL, thread_work, (void *)t);

    for (long t = 0; t < num_threads; t++)
        pthread_join(threads[t], NULL);
    int64_t end = getTimeMillis();

    pthread_mutex_destroy(&mutex);
    printf("\nMain thread: shared_counter: %ld\n", shared_counter);
    printf("Main thread: Elapsed time: %ld (msec)\n", end-start);
    return 0;
}