#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

#define N 10

void allocate_memory_array(int** ptr_array,int n);
void show_array(int* array);
void fill_array_random(int* array, int min, int max);

int main(int argc, char** argv) {


    int process_id;
    int process_amount;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &process_amount);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    int data_amount = N / (process_amount - 1 );
    int last_data_amount = data_amount + N % (process_amount - 1 );

    if ( process_id == 0 ) {

        int* array_a;
        int* array_b;
        int* array_c;
        allocate_memory_array(&array_a,N);
        allocate_memory_array(&array_b,N);
        allocate_memory_array(&array_c,N);

        fill_array_random(array_a,1,99);
        fill_array_random(array_b,1,99);

        for (int i = 1; i <= process_amount - 1 ; i++ ){
            if ( i == ( process_amount - 1 ) ){
                MPI_Send(&array_a[(i-1)*data_amount], last_data_amount, MPI_INT, i,0, MPI_COMM_WORLD);
                MPI_Send(&array_b[(i-1)*data_amount], last_data_amount, MPI_INT, i,0, MPI_COMM_WORLD);
                MPI_Send(&array_c[(i-1)*data_amount], last_data_amount, MPI_INT, i,0, MPI_COMM_WORLD);
            }
            MPI_Send(&array_a[(i-1)*data_amount], data_amount , MPI_INT, i,0, MPI_COMM_WORLD);
            MPI_Send(&array_b[(i-1)*data_amount], data_amount , MPI_INT, i,0, MPI_COMM_WORLD);
            MPI_Send(&array_c[(i-1)*data_amount], data_amount , MPI_INT, i,0, MPI_COMM_WORLD);
        }

        for ( int i = 1; i <= process_amount-1 ; i++ ){
            MPI_Recv(array_c, data_amount, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //MPI_Recv(array_c, last_data_amount, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("[+] Array A:\n");
        show_array(array_a);
        printf("[+] Array B:\n");
        show_array(array_b);
        printf("[+] Array C:\n");
        show_array(array_c);

    } else {

        if ( process_id == process_amount - 1 )
            data_amount = last_data_amount;

        int* array_a_parcial;
        int* array_b_parcial;
        int* array_c_parcial;
        allocate_memory_array(&array_a_parcial,N);
        allocate_memory_array(&array_b_parcial,N);
        allocate_memory_array(&array_c_parcial,N);

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

void allocate_memory_array(int** ptr_array,int n) {
    *ptr_array = (int*) malloc( n * sizeof(int) );
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
