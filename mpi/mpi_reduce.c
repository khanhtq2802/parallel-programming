#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to print the 2D array
void printArray(int *array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i * cols + j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    int rank, size;
    int m = 4, n = 5; // Dimensions of the array (change as needed)
    int A[m][n];
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Initialize the array (this should be done by rank 0)
    if (rank == 0) {
        int counter = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = counter++;
            }
        }
        printf("Original array at rank 0:\n");
        printArray(&A[0][0], m, n);
    }
    
    // Scatter the array to all processes
    int local_size = (m * n) / size;
    int local_array[local_size];
    MPI_Scatter(&A[0][0], local_size, MPI_INT, local_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    // Calculate local max and sum
    int local_max = INT_MIN;
    int local_sum = 0;
    for (int i = 0; i < local_size; i++) {
        if (local_array[i] > local_max) {
            local_max = local_array[i];
        }
        local_sum += local_array[i];
    }
    
    // Reduce to find global max and sum at rank 0
    int global_max, global_sum;
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    // Print the results at rank 0
    if (rank == 0) {
        printf("Global Max using MPI_Reduce: %d\n", global_max);
        printf("Global Sum using MPI_Reduce: %d\n", global_sum);
    }
    
    // Use MPI_Allreduce to find global max and sum at all ranks
    MPI_Allreduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    
    // Print the results at all ranks
    printf("Rank %d - Global Max using MPI_Allreduce: %d\n", rank, global_max);
    printf("Rank %d - Global Sum using MPI_Allreduce: %d\n", rank, global_sum);
    
    MPI_Finalize();
    return 0;
}
