#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 2
#define MAX_COUNT 10000000

volatile int counter = 0;
pthread_mutex_t mutex;

int64_t getTimeMillis(void) {
    struct timespec tm;

    if (clock_gettime(CLOCK_MONOTONIC, &tm) == -1) {
        perror("clock_gettime");
        return 0;
    } else return tm.tv_sec*1000LL + tm.tv_nsec/1000000LL;
}

void *increment(void *threadid) {
    for (int i = 0; i < MAX_COUNT; ++i) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *decrement(void *threadid) {
    for (int i = 0; i < MAX_COUNT; ++i) {
        while (counter == 0)
            ;
        pthread_mutex_lock(&mutex);
        counter--;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    long start = getTimeMillis();
    // Create increment thread
    rc = pthread_create(&threads[0], NULL, increment, (void *)0);
    if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }

    // Create decrement thread
    rc = pthread_create(&threads[1], NULL, decrement, (void *)1);
    if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }

    // Join threads
    for (t = 0; t < NUM_THREADS; ++t) {
        rc = pthread_join(threads[t], NULL);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    long end = getTimeMillis();

    // Print final value of counter
    printf("Final value of counter: %d\n", counter);
    printf("Execution time: %ld\n", end - start);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    pthread_exit(NULL);
}
