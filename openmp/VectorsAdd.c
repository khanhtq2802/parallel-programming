#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void sum_arrays(int* a, int* b, int* c, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

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
    sum_arrays(a, b, c, size);

    // Display the result
    printf("Resultant array c:\n");
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
