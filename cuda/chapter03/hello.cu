#include <stdio.h>

#define CUDA_CHECK_ERROR()                                                          \
    do                                                                              \
    {                                                                               \
        cudaError_t err = cudaGetLastError();                                       \
        if (err != cudaSuccess)                                                     \
        {                                                                           \
            printf("CUDA error: %s, line %d\n", cudaGetErrorString(err), __LINE__); \
            exit(EXIT_FAILURE);                                                     \
        }                                                                           \
    } while (0)

__global__ void helloCUDA()
{
    printf("Hello CUDA from GPU!\n");
}

int main()
{
    helloCUDA<<<1, 1>>>();
    CUDA_CHECK_ERROR();
    cudaDeviceSynchronize();
    CUDA_CHECK_ERROR();
    return 0;
}
