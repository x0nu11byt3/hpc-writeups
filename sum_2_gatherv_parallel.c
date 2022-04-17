#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

#define N 10

void memory_allocate_array(int** ptr_array,int n);
void memory_allocate_grid(int** ptr_array,int n, int process_amount);
void show_array(int* array);
void fill_array_random(int* array, int min, int max);

int main(int argc, char** argv) {

    MPI_Comm comm;
    int process_id, process_amount, root;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm, &process_amount);
    MPI_Comm_rank(comm, &process_id);
    // WARNING! first attempt for calculate size_recv_buffer
    int size_recv_buffer = ( N * process_amount ) * process_amount;
    int data_amount = N / (process_amount - 1 );
    int* data_grid;
    int* recv_counts;
    int* displacements;
    int count_displacements = 0;

    // arrays to sum a + b
    int* array_a;
    int* array_b;
    // array result
    int* array_c;

    memory_allocate_array(&array_a,N);
    memory_allocate_array(&array_b,N);
    memory_allocate_array(&array_c,N);

    fill_array_random(array_a,1,99);
    fill_array_random(array_b,1,99);

    memory_allocate_grid(&data_grid,N, process_amount);

    memory_allocate_array(&recv_counts,process_amount);
    memory_allocate_array(&displacements,process_amount);

    // WARNING! here I have to fill in my grid with the data of both arrangements and their due summation.
    // data_grid =

    // first attempt for calculate recv_counts & displacements
    for (int i = 0; i < process_amount; i++) {
        recv_counts[i] = N;
        displacements[i] = i * N;
    }

    // WARNING! here I have to make sum operation array_a + array_b for to get array_c

     MPI_Scatterv(array_a,recv_counts,displacements,MPI_INT,data_grid,size_recv_buffer,MPI_INT,0,MPI_COMM_WORLD);
     MPI_Scatterv(array_b,recv_counts,displacements,MPI_INT,data_grid,size_recv_buffer,MPI_INT,0,MPI_COMM_WORLD);

     MPI_Gatherv(array_a,N,MPI_INT,data_grid,recv_counts,displacements,MPI_INT,0,MPI_COMM_WORLD);
     MPI_Gatherv(array_b,N,MPI_INT,data_grid,recv_counts,displacements,MPI_INT,0,MPI_COMM_WORLD);

    MPI_Finalize();

   return 0;
}

void memory_allocate_array(int** ptr_array,int n) {
    *ptr_array = (int*) malloc( n * sizeof(int) );
}

void memory_allocate_grid(int** ptr_array,int n, int process_amount) {
    *ptr_array = (int*) malloc( process_amount * n * sizeof(int) );
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
