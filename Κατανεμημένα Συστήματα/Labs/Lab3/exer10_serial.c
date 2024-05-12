#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

volatile double A[N][N];
volatile double B[N][N];
volatile double C[N][N];

void mat_mul2D(void) {
    int i, j, k;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

int main(int argc, char* argv[]) {
    for (long i = 0; i < N; i++) {
        for (long j = 0; j < N; j++) {
            A[i][j] = i + j;
            if (i == j) B[i][j] = 1.0;
            else B[i][j] = 0.0;
        }
    }

    mat_mul2D();
    if (N < 20) {
        for (long i = 0; i < N; i++) {
            for (long j = 0; j < N; j++) {
                printf("C[%ld][%ld] = %.2lf \t", i, j, C[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}