#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
// #include <assert.h>


#define N 1000
#define RUNS 1
double A[N][N], B[N][N], C[N][N], D[N][N];

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Check if the number of MPI processes matches the required number of runs
    // assert(size == RUNS);

    srand(42);

    // Populate A and B arrays
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            A[i][j] = rand();
            B[i][j] = rand();
        }

    // Broadcast matrices A and B to all MPI processes
    MPI_Bcast(A, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);



    double  start_time = MPI_Wtime();

    for(int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }

    double end_time = MPI_Wtime();
    double elapsed_time = end_time - start_time;


    // Print the time taken by each MPI process
    printf("Process %d: %f seconds\n", rank, elapsed_time);
}