#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

#define N 10

void show_array(int* array);
void fill_array_random(int* array, int min, int max);

int main(int argc, char** argv) {

    int rank, gsize, root, i;
    int *displacements, *displacements_counts;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &gsize);

    root = 0;

    int *array_a = (int*) malloc( gsize * N * sizeof(int) );
    int *array_b = (int*) malloc( gsize * N * sizeof(int) );
    int  *read_buffer_array_a = (int*) malloc( N * sizeof(int) );
    int  *read_buffer_array_b = (int*) malloc( N * sizeof(int) );;

    fill_array_random(read_buffer_array_a, 2, 99);
    fill_array_random(read_buffer_array_b, 2, 99);

    displacements = (int *) malloc( gsize * sizeof(int));
    displacements_counts = (int *) malloc( gsize * sizeof(int));

    for (i = 0; i < gsize; ++i) {
        displacements[i] = i*N;
        displacements_counts[i] = N;
    }

    MPI_Scatterv( array_a, displacements_counts, displacements, MPI_INT, read_buffer_array_a, N, MPI_INT,root, MPI_COMM_WORLD);
    MPI_Scatterv( array_b, displacements_counts, displacements, MPI_INT, read_buffer_array_b, N, MPI_INT,root, MPI_COMM_WORLD);

    MPI_Finalize();

   return 0;
}

void show_array(int* array) {
    for (int i = 0; i < N ; i++)
        printf("item[%d]: %d \n",i,array[i]);
}

void fill_array_random(int* array, int min, int max) {
    time_t seconds = (time(NULL))/3600;
    srand ( seconds );
    for (int i = 0; i < N ; i++){
        int random = ((rand() % (max - min + 1)) + min) + (seconds/20000);
        array[i] = random;
    }
}
