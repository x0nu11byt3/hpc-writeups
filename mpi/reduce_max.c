#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

#define N 10

void show_array(int* array, int n);
void fill_array_random(int* array, int min, int max);

int main(int argc, char** argv) {

    int rank, gsize, root;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &gsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* send_buffer = (int*) malloc( N * sizeof(int) );
    int* recv_buffer = (int*) malloc( gsize * sizeof(int) );;

    MPI_Reduce(send_buffer,recv_buffer,gsize,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);

    if ( rank == 0 ) {
        for ( int i = 1; i <= gsize; i++ ){
            printf(":: Init Array[%d] \n",i);
            show_array(send_buffer,N);
        }

        printf(":: Result Array with maximum values: \n");
        show_array(recv_buffer,gsize);
    }

    MPI_Finalize();
    return 0;
}

void show_array(int* array,int n) {
    for (int i = 0; i < n ; i++)
        printf("item[%d]: %d \n",i,array[i]);
}

void fill_array_random(int* array, int min, int max) {
    srand ( time(NULL) );
    for (int i = 0; i < N ; i++){
        int random = (rand() % (max - min + 1)) + min;
        array[i] = random;
    }
}
