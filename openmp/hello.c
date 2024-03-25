// gcc -fopenmp hello.c

#include <stdio.h>
#include <omp.h>

int main() {
    // Set the number of threads
    omp_set_num_threads(4); // Adjust the number of threads as needed
    // Parallel region starts here
    #pragma omp parallel
    {
        // Get the thread number
        int thread_num = omp_get_thread_num();
        // Print "Hello, World!" with the thread number
        printf("Hello, World! I'm thread %d\n", thread_num);
    }
    // Parallel region ends here
    return 0;
}