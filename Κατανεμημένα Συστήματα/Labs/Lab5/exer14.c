#include <stdio.h>
#include <omp.h>


int main(void) {

    #pragma omp parallel num_threads(8)
    {
        printf("I'm the thread with id=%d -- Total threads: %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    return 0;
}
