#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>

__global__ void cuda_hello_world(){
    printf("[+] Hello World from GPU!\n");
}

int main() {
    cuda_hello_world<<<1,1>>>();
    return 0;
}
