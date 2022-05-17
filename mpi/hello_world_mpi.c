#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {

    int rank, gsize;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &gsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hello World from process %d of %d\n", rank, gsize);

    MPI_Finalize();
    return 0;

}
