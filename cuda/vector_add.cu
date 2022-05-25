#include <__clang_cuda_builtin_vars.h>
#include <stdio.h>
#include <time.h>
#include <cuda.h>
#include <cuda_runtime.h>

#define N_THREADS 10
#define THREADS_PER_BLOCK 2
#define N_BLOCKS 5

/* Kernel definition vector add */
__global__ void vector_add(float *a, float *b, float *c){
    int i =  blockDim.x * blockIdx.x + threadIdx.x;
    while ( i < N_THREADS ) {
        c[i] = a[i] + b[i];
        i += blockDim.x;
    }
}

/* Fill array with random values  */
void fill_array_random(float *array, int min, int max){
    time_t seconds = (time(NULL))/3600;
    srand(seconds);
    for (int i = 0; i < N_THREADS; i++  ) {
        float random = ((rand() % (max - min + 1))+min);
        array[i] = random;
    }
}

int main(int argc, char** argv) {

    /* Init host code */
    size_t size = N_THREADS * sizeof(float);

    /* Allocate input vectors host_a & host_b in host memory (RAM) */
    float *host_a = (float*)malloc(size);
    float *host_b = (float*)malloc(size);
    float *host_c = (float*)malloc(size);

    /* Inicialize input vectors */
    fill_array_random(host_a, 1, 99);
    fill_array_random(host_b, 1, 99);

    /* Allocate vectors in device memory (VRAM) */
    float *device_a, *device_b, *device_c;
    cudaMalloc( (void**)&device_a, size );
    cudaMalloc( (void**)&device_b, size );
    cudaMalloc( (void**)&device_c, size );

    /* Copy input vectors from host memory to device memory */
    cudaMemcpy(device_a,host_a,size,cudaMemcpyHostToDevice);
    cudaMemcpy(device_b,host_b,size,cudaMemcpyHostToDevice);

    /*Invoke Kernel */
    //int threads_per_block = 256;
    //int blocks_per_grid = (N_THREADS + threads_per_block - 1) / threads_per_block;
    //vector_add<<<blocks_per_grid,threads_per_block>>>(device_a,device_b,device_c);
    //vector_add<<<1,N_THREADS>>>(device_a,device_b,device_c);
    vector_add<<<N_BLOCKS,N_THREADS>>>(device_a,device_b,device_c);
    /* Copy result from device memory to host memory */
    cudaMemcpy(host_c,device_c,size,cudaMemcpyDeviceToHost);

    for (int i = 0; i < N_THREADS; i++  )
        printf("%f +  %f = %f \n" ,host_a[i],host_b[i], host_c[i]);

    /* Free host memory */
    free(host_a);
    free(host_b);
    free(host_c);

    /* Free device memory */
    cudaFree(device_a);
    cudaFree(device_b);
    cudaFree(device_c);

    return 0;
}
