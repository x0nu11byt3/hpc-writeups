#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>

#define N 10

void show_array(int* array);
void fill_array(int* array);
int sum(int* array);

int main(int argc, char** argv) {

    int sum = 0;
    int parcial_sum;

    int process_id;
   // int process_amount = atoi(argv[2]);
    int process_amount = 2;

    int data_amount = N / (process_amount - 1 );
    int last_data_amount = data_amount + N % (process_amount - 1 );

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &process_amount);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    if ( process_id == 0 ) {

        int array_a[N] = {1,2,3,4,5,6,7,8,9,10};
        //fill_array(&array_a);

        for (int i = 1; i <= process_amount - 1 ; i++ ){
            if ( i == ( process_amount - 1 ) )
                MPI_Send(&array_a[(i-1)*data_amount], last_data_amount, MPI_INT, i,0, MPI_COMM_WORLD);
            MPI_Send(&array_a[(i-1)*data_amount], data_amount , MPI_INT, i,0, MPI_COMM_WORLD);
        }

        for ( int i = 1; i <= (process_amount-1) ; i++ ) {
            MPI_Recv(&parcial_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += parcial_sum;
        }

        show_array(array_a);
        printf("Total Sum: %d \n ", sum);

    } else {

        if ( process_id == process_amount - 1 )
            data_amount = last_data_amount;

        int array_parcial[data_amount];

        MPI_Recv(array_parcial,data_amount , MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < data_amount - 1 ; i++ )
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

void fill_array(int* array) {
    for (int i = 0; i < N ; i++){
        int val;
        printf("Enter a Integer number: ");
        scanf("%d",&val);
        array[i] = val;
    }
}

int sum(int* array) {
    int sum = 0;
    for (int i = 0; i < N ; i++)
        sum += array[i];
    return sum;
}

