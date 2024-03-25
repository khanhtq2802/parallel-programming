// gcc -fopenmp HelloWorld.c

#include <stdio.h>
#include <omp.h>

int main()
{
    // omp_set_num_threads(10);
    // printf("%d", omp_get_num_threads());
    #pragma omp parallel
    {
        int threadnumber = omp_get_num_threads();
        int threadID = omp_get_thread_num();

        printf("Hello from thread %d, nthreads %d\n", threadID, threadnumber);        
    }
    return 0;
}