#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) 
{
    int N = 200;
    int A[N];
    for(int i = 0; i < N; i++){
        A[i] = i;
    }
    MPI_Init(&argc, &argv);
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int sum = 0;
    int domain_size = N / world_size;
    if (world_rank != world_size - 1)
    {
        for(int i = world_rank*domain_size; i < (world_rank + 1)*domain_size; i++){
            sum += A[i];
        }
    } else {
        for(int i = world_rank*domain_size; i < N; i++){
            sum += A[i];
        }
    }

    if (world_rank != 0){
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        int other_sum;
        for(int i = 1; i < world_size; i++){
            MPI_Recv(&other_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += other_sum;
        }
        printf("sum = %d\n", sum);
    }
    MPI_Finalize();
}