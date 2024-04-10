#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int Nr_of_CPU, ID_of_CPU;
    MPI_Comm_size(MPI_COMM_WORLD, &Nr_of_CPU);
    MPI_Comm_rank(MPI_COMM_WORLD, &ID_of_CPU);
    printf("Hello world from processor rank %d out of %d processors\n", ID_of_CPU, Nr_of_CPU);
    MPI_Finalize();
}