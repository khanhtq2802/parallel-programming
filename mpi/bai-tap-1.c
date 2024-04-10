#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int number;
    if (world_rank == 0) {
        int A[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        MPI_Send(A, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        int B[10], C[10];
        MPI_Recv(B, 10, MPI_INT, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        for(int i = 0; i < 10; i++){
            C[i] = B[i]*2;
            printf("%d ", C[i]);
        }
    }
    printf("\n");
    MPI_Finalize();
}