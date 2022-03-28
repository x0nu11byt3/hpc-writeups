#include <stdio.h>

#define N 100

void show_array(int* array);
void fill_array(int* array);

int sum(int* array);

int main(int argc, char** argv) {

    int array[N] = {};
    fill_array(array);
    show_array(array);
    int add = sum(array);
    printf("sum: %d \n", add);
    return 0;
}


void show_array(int* array) {
    for (int i = 0; i < N ; i++)
        printf(" %d \n",array[i]);
}

void fill_array(int* array) {

    for (int i = 0; i < N ; i++){
        int val;
        printf("Eneter a Integer number: ");
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
