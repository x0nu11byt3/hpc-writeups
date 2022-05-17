#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>

#define N 10

void show_array(int* array);
void fill_array_random(int* array, int min, int max);
int sum(int* array);

int main(int argc, char** argv) {

    int sum = 0;
    int parcial_sum, i, rank, gsize;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &gsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data_amount = N / (gsize - 1 );
    int last_data_amount = data_amount + ( N % (gsize - 1 ) );

    if ( rank == 0 ) {

        int *array_a = (int*) malloc( N * sizeof(int) );
        fill_array_random(array_a,1,99);

        for ( i = 1; i <= gsize - 1  ; i++ ){
            if ( i == ( gsize - 1 ) )
                MPI_Send(&array_a[(i-1)*data_amount], last_data_amount, MPI_INT, i,0, MPI_COMM_WORLD);
            MPI_Send(&array_a[(i-2)*data_amount], data_amount , MPI_INT, i,0, MPI_COMM_WORLD);
        }

        for ( i = 1; i <= (gsize-1) ; i++ ) {
            MPI_Recv(&parcial_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += parcial_sum;
        }

        show_array(array_a);
        printf("Total Sum: %d \n ", sum);

    } else {

        if ( rank == gsize - 1 ) {
            data_amount = last_data_amount;
            printf("last_data_amount: %d ",last_data_amount);
        }

        int *array_parcial = (int*) malloc( data_amount * sizeof(int) );;
        MPI_Recv(array_parcial,data_amount , MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for ( i = 0; i < data_amount - 1  ; i++ )
            sum += array_parcial[i];

        MPI_Send(&sum, 1, MPI_INT, 0,0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

   return 0;
}


void show_array(int* array) {
    for (int i = 0; i < N ; i++)
        printf(" %d \n",array[i]);
}

void fill_array_random(int* array, int min, int max) {
    for (int i = 0; i < N ; i++){
        int random = (rand() % (max - min + 1)) + min;
        array[i] = random;
    }
}

int sum(int* array) {
    int sum = 0;
    for (int i = 0; i < N ; i++)
        sum += array[i];
    return sum;
}
