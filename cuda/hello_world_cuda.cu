#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>

#define N_THREADS 1

// kernel definition hello World
__global__ void cuda_hello_world(){
    printf("[+] Hello World from GPU!\n");
}

int main(int argc, char** argv) {

    // kernel invocation with N threads
    cuda_hello_world<<<1,N_THREADS>>>();

    return 0;
}
