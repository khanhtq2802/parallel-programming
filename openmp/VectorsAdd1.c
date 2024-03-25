#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int size = 20; // Size of the arrays
    int *a, *b, *c;

    // Allocate memory for arrays
    a = (int*)malloc(size * sizeof(int));
    b = (int*)malloc(size * sizeof(int));
    c = (int*)malloc(size * sizeof(int));

    // Initialize arrays a and b
    for (int i = 0; i < size; i++) {
        a[i] = i;
        b[i] = 2 * i;
    }

    // Compute the sum of arrays a and b into c
    omp_set_num_threads(size);
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        c[threadID] = a[threadID] + b[threadID];
    }
    // Display the result
    printf("array a:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("array b:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    printf("array c:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    free(a);
    free(b);
    free(c);

    return 0;
}
