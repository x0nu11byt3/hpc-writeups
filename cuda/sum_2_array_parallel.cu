#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>

#define N_THREADS 2

/* kernel definition vector add */
__global__ void vector_add(float *a, float *b, float *c){
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

int main() {

    /* Init host code */
    size_t size = N_THREADS * sizeof(float);

    /* Allocate input vectors host_a & host_b in host memory (RAM) */
    float *host_a = (float*)malloc(size);
    float *host_b = (float*)malloc(size);
    float *host_c = (float*)malloc(size);

    /* Allocate vectors in device memory (VRAM) */
    float *device_a, *device_b, *device_c;
    cudaMalloc(&device_a,size);
    cudaMalloc(&device_b,size);
    cudaMalloc(&device_c,size);

    /* Copy result from device memory to host memory */
    cudaMemcpy(device_a,host_a,size,cudaMemcpyHostToDevice);
    cudaMemcpy(device_b,host_b,size,cudaMemcpyHostToDevice);

    /*Invoke Kernel */
    vector_add<<<1,N_THREADS>>>(device_a,device_b,device_c);

    /* Free device memory */
    cudaFree(device_a);
    cudaFree(device_b);
    cudaFree(device_c);

    return 0;
}
