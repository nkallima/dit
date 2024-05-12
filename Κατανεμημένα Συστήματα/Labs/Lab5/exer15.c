#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define POINT_A 0.0
#define POINT_B 100.0

double f(double x) {
    double return_val;

    return_val = x*x;
    return return_val;
}

double Trap(double a, double b, int n) {
    double  h, x, my_result;
    double  local_a, local_b;
    int  i, local_n;
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    h = (b-a)/n; 
    local_n = n/thread_count;  
    local_a = a + my_rank*local_n*h; 
    local_b = local_a + local_n*h; 
    my_result = (f(local_a) + f(local_b))/2.0; 
    for (i = 1; i <= local_n-1; i++) {
        x = local_a + i*h;
        my_result += f(x);
    }
    my_result = my_result*h; 

    return my_result; 
}


int main(int argc, char* argv[]) {
    int num_threads;

    if (argc != 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return EXIT_FAILURE;
    }
    num_threads = atoi(argv[1]);
    if (num_threads <= 0) {
        printf("Number of threads must be a positive integer.\n");
        return EXIT_FAILURE;
    }

#   pragma omp parallel num_threads(num_threads)
    {
        double result = Trap(POINT_A, POINT_B, 100000000);
        printf("I'm the thread with id=%d -- Total threads: %d -- Result: %.15lf\n",
               omp_get_thread_num(), omp_get_num_threads(), result);
    }

    return 0;
}
