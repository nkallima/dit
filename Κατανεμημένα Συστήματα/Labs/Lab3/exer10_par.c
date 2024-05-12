#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

volatile double A[N][N];
volatile double B[N][N];
volatile double C[N][N];
volatile unsigned int num_threads;

void *thread_work(void *arg) {
    long mytid = (long)arg;

    int chunk_size = N / num_threads;
    int start = mytid * chunk_size;
    int end = (mytid + 1) * chunk_size;
    if (mytid == num_threads - 1) {
        // Adjust the end of the last thread to cover any remaining elements
        end = N;
    }

    printf("Thread: %ld -- Performs matrix mul: start: %d - end: %d\n", mytid, start, end - 1);
    int i, j, k;
    for (i = start; i < end; ++i) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
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

    for (long i = 0; i < N; i++) {
        for (long j = 0; j < N; j++) {
            A[i][j] = i + j;
            if (i == j) B[i][j] = 1.0;
            else B[i][j] = 0.0;
        }
    }
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    // Create threads
    for (long t = 0; t < num_threads; t++)
        pthread_create(&threads[t], NULL, thread_work, (void *)t);
    printf("This is the main thread\n");
    for (long t = 0; t < num_threads; t++)
        pthread_join(threads[t], NULL);
    if (N < 20) {
        for (long i = 0; i < N; i++) {
            for (long j = 0; j < N; j++) {
                printf("C[%ld][%ld] = %.2lf \t", i, j, C[i][j]);
            }
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}