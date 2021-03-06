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

    int rank;
    int gsize;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &gsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *array = (int*) malloc( N * sizeof(int) );

    fill_array_random(array,1,99);

    MPI_Bcast(array,N,MPI_INT,0,MPI_COMM_WORLD);
    show_array(array);
    MPI_Finalize();

    return 0;
}

void show_array(int* array) {
    for (int i = 0; i < N ; i++)
        printf("item[%d]: %d \n",i,array[i]);
}

void fill_array_random(int* array, int min, int max) {
    for (int i = 0; i < N ; i++){
        int random = (rand() % (max - min + 1)) + min;
        array[i] = random;
    }
}
