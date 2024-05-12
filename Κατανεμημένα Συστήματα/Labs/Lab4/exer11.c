#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define MAX_COUNT 1000000

volatile int counter = 0;
pthread_mutex_t mutex;

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

    // Print final value of counter
    printf("Final value of counter: %d\n", counter);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    pthread_exit(NULL);
}
