#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

#define N 10

void memory_allocate_array(int** ptr_array,int n);
void show_array(int* array, int n);
void fill_array_random(int* array, int min, int max);

int main(int argc, char** argv) {

    //MPI_Comm comm;
    int process_id, process_amount, root;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &process_amount);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    int* send_buffer;
    memory_allocate_array(&send_buffer,N);
    fill_array_random(send_buffer,1,99);

    int* recv_buffer;
    memory_allocate_array(&recv_buffer,process_amount);

    MPI_Reduce(send_buffer,recv_buffer,process_amount,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);

    if ( process_id == 0 ) {
        for ( int i = 1; i <= process_amount; i++ ){
            printf(":: Init Array[%d] \n",i);
            show_array(send_buffer,N);
        }

        printf(":: Result Array with minimum values: \n");
        show_array(recv_buffer,process_amount);
    }

    MPI_Finalize();

   return 0;
}

void memory_allocate_array(int** ptr_array,int n) {
    *ptr_array = (int*) malloc( n * sizeof(int) );
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
