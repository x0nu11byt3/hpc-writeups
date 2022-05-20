#include <stdio.h>
#include <time.h>
#include <cuda.h>
#include <cuda_runtime.h>

#define N_THREADS 4

/* kernel definition vector add */
__global__ void vector_add(float *a, float *b, float *c){
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

void fill_array_random(float *array, int min, int max){
    time_t seconds = (time(NULL))/3600;
    srand(seconds);

    for (int i = 0; i < N_THREADS; i++  ) {
        float random = ((rand() % (max - min + 1))+min);
        array[i] = random;
    }
}

int main() {

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
    cudaMalloc(&device_a,size);
    cudaMalloc(&device_b,size);
    cudaMalloc(&device_c,size);

    /* Copy input vectors from host memory to device memory */
    cudaMemcpy(device_a,host_a,size,cudaMemcpyHostToDevice);
    cudaMemcpy(device_b,host_b,size,cudaMemcpyHostToDevice);

    /*Invoke Kernel */
    vector_add<<<1,N_THREADS>>>(device_a,device_b,device_c);

    /* Copy result from device memory to host memory */
    cudaMemcpy(host_c,device_c,size,cudaMemcpyDeviceToHost);

    for (int i = 0; i < N_THREADS; i++  )
        printf(" total: %f \n" , host_c[i]);

    /* Free device memory */
    cudaFree(device_a);
    cudaFree(device_b);
    cudaFree(device_c);

    return 0;
}
