#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

#define N 10

void memory_allocate_array(int** ptr_array,int n);
void memory_allocate_grid(int** ptr_array,int n, int gsize);
void show_array(int* array);
void fill_array_random(int* array, int min, int max);

int main(int argc, char** argv) {

    //MPI_Comm comm;
    int rank, gsize, root, i;
    int *displacements, *displacements_counts;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &gsize);

    root = 0;

    int *array_a;
    //int  read_buffer_array_a[N];
    int  *read_buffer_array_a;
    int *array_b;
    //int  read_buffer_array_b[N];
    int  *read_buffer_array_b;

    memory_allocate_array(&read_buffer_array_a,N);
    memory_allocate_array(&read_buffer_array_b,N);

    memory_allocate_grid(&array_a,N, gsize);
    memory_allocate_grid(&array_b,N, gsize);

    fill_array_random(read_buffer_array_a, 2, 99);
    fill_array_random(read_buffer_array_b, 2, 99);

    displacements = (int *)malloc(gsize*sizeof(int));
    displacements_counts = (int *)malloc(gsize*sizeof(int));
    for (i = 0; i < gsize; ++i) {
        displacements[i] = i*N;
        displacements_counts[i] = N;
    }

    MPI_Scatterv( array_a, displacements_counts, displacements, MPI_INT, read_buffer_array_a, N, MPI_INT,root, MPI_COMM_WORLD);
    MPI_Scatterv( array_b, displacements_counts, displacements, MPI_INT, read_buffer_array_b, N, MPI_INT,root, MPI_COMM_WORLD);

    //show_array(read_buffer_array_a);
    //show_array(read_buffer_array_b);

    MPI_Finalize();

   return 0;
}

void memory_allocate_array(int** ptr_array,int n) {
    *ptr_array = (int*) malloc( n * sizeof(int) );
}

void memory_allocate_grid(int** ptr_array,int n, int gsize) {
    *ptr_array = (int*) malloc( gsize * n * sizeof(int) );
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
