#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

#define N 10

typedef struct {
    int x, y , z;
} Point;

void allocate_memory_point_array(int** ptr_array,int n);
void print_points(Point* points);
void fill_array_random(int* array, int min, int max);
void point_fill_coordinates(Point *points,int min, int max);

int main(int argc, char** argv) {

    int rank;
    int gsize;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &gsize);

    MPI_Datatype datatype_point;
    MPI_Type_contiguous(3, MPI_INT, &datatype_point);
    MPI_Type_commit(&datatype_point);

    Point points_array_a[N];
    Point points_array_b[N];
    Point points_array_c[N];

    int data_amount = N / (gsize - 1 );
    int last_data_amount = data_amount + N % (gsize - 1 );

    if ( rank == 0 ) {

        point_fill_coordinates(points_array_a, 1,99);
        point_fill_coordinates(points_array_b, 1,99);

        for (int i = 1; i <= gsize - 1 ; i++ ){
            if ( i == ( gsize - 1 ) ){
                MPI_Send(&points_array_a[(i-1)*data_amount], last_data_amount, datatype_point, i,0, MPI_COMM_WORLD);
                MPI_Send(&points_array_b[(i-1)*data_amount], last_data_amount, datatype_point, i,0, MPI_COMM_WORLD);
                MPI_Send(&points_array_c[(i-1)*data_amount], last_data_amount, datatype_point, i,0, MPI_COMM_WORLD);
            }
            MPI_Send(&points_array_a[(i-1)*data_amount], data_amount , datatype_point, i,0, MPI_COMM_WORLD);
            MPI_Send(&points_array_b[(i-1)*data_amount], data_amount , datatype_point, i,0, MPI_COMM_WORLD);
            MPI_Send(&points_array_c[(i-1)*data_amount], data_amount , datatype_point, i,0, MPI_COMM_WORLD);
        }

        for ( int i = 1; i <= gsize-1 ; i++ )
            MPI_Recv(points_array_c, data_amount, datatype_point, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("[+] Points A:\n");
        print_points(points_array_a);
        printf("[+] Points B:\n");
        print_points(points_array_a);

        printf("[+] Points C:\n");
        print_points(points_array_c);


    } else {

        if ( rank == gsize - 1 )
            data_amount = last_data_amount;

        Point points_array_a_parcial[N];
        Point points_array_b_parcial[N];
        Point points_array_c_parcial[N];

        MPI_Recv(points_array_a_parcial,data_amount , datatype_point, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(points_array_b_parcial,data_amount , datatype_point, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(points_array_c_parcial,data_amount , datatype_point, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < data_amount - 1 ; i++ ){
            points_array_c_parcial[i].x = points_array_a_parcial[i].x + points_array_b_parcial[i].x;
            points_array_c_parcial[i].y = points_array_a_parcial[i].y + points_array_b_parcial[i].y;
            points_array_c_parcial[i].z = points_array_a_parcial[i].z + points_array_b_parcial[i].z;
        }
        MPI_Send(points_array_c_parcial, data_amount, datatype_point, 0,0, MPI_COMM_WORLD);
    }

    MPI_Type_free(&datatype_point);
    MPI_Finalize();

   return 0;
}

void allocate_memory_point_array(int** ptr_array,int n) {
    *ptr_array = (int*) malloc( n * (3 * sizeof(int)) );
}

void print_points(Point* points) {
    for (int i = 0; i < N ; i++)
        printf("x: %d , y: %d , z: %d \n",points[i].x,points[i].y,points[i].z);
}

void fill_array_random(int* array, int min, int max) {
    for (int i = 0; i < N ; i++){
        int random = (rand() % (max - min + 1)) + min;
        array[i] = random;
    }
}

void point_fill_coordinates(Point *points, int min, int max){

    time_t seconds = (time(NULL))/3600;
    srand ( seconds );

    for (int i = 0; i < N; ++i) {
        points[i].x = ((rand() % (max - min + 1)) + min) + (seconds/10000);
        points[i].y = ((rand() % (max - min + 1)) + min) + (seconds/20000);
        points[i].z = ((rand() % (max - min + 1)) + min) + (seconds/30000);
    }

}
