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

    int data_amount = N / (gsize - 1 );
    int last_data_amount = data_amount + N % (gsize - 1 );

    if ( rank == 0 ) {

        int* array_a = (int*) malloc( N * sizeof(int) );;
        int* array_b = (int*) malloc( N * sizeof(int) );;
        int* array_c = (int*) malloc( N * sizeof(int) );;

        fill_array_random(array_a,1,99);
        fill_array_random(array_b,1,99);

        for (int i = 1; i <= gsize - 1 ; i++ ){
            if ( i == ( gsize - 1 ) ){
                MPI_Send(&array_a[(i-1)*data_amount], last_data_amount, MPI_INT, i,0, MPI_COMM_WORLD);
                MPI_Send(&array_b[(i-1)*data_amount], last_data_amount, MPI_INT, i,0, MPI_COMM_WORLD);
                MPI_Send(&array_c[(i-1)*data_amount], last_data_amount, MPI_INT, i,0, MPI_COMM_WORLD);
            }
            MPI_Send(&array_a[(i-1)*data_amount], data_amount , MPI_INT, i,0, MPI_COMM_WORLD);
            MPI_Send(&array_b[(i-1)*data_amount], data_amount , MPI_INT, i,0, MPI_COMM_WORLD);
            MPI_Send(&array_c[(i-1)*data_amount], data_amount , MPI_INT, i,0, MPI_COMM_WORLD);
        }

        for ( int i = 1; i <= gsize-1 ; i++ )
            MPI_Recv(array_c, data_amount, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("[+] Array A:\n");
        show_array(array_a);
        printf("[+] Array B:\n");
        show_array(array_b);
        printf("[+] Array C:\n");
        show_array(array_c);

    } else {

        if ( rank == gsize - 1 )
            data_amount = last_data_amount;

        int* array_a_parcial = (int*) malloc( N * sizeof(int) );
        int* array_b_parcial = (int*) malloc( N * sizeof(int) );
        int* array_c_parcial = (int*) malloc( N * sizeof(int) );

        MPI_Recv(array_a_parcial,data_amount , MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(array_b_parcial,data_amount , MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(array_c_parcial,data_amount , MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < data_amount - 1 ; i++ )
            array_c_parcial[i] = array_a_parcial[i] + array_b_parcial[i];

        MPI_Send(array_c_parcial, data_amount, MPI_INT, 0,0, MPI_COMM_WORLD);
    }
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
