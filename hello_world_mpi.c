#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {

    int process_id, process_amount;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &process_amount);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    printf("Hello World from process %d of %d\n", process_id, process_amount);

    MPI_Finalize();
    return 0;

}
