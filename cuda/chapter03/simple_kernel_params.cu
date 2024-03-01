#include "../common/book.h"

__global__ void add(int a, int b, int *c)
{
    *c = a + b; // thay doi gia chi o dia tri duoc pass vao
}

int main(void)
{
    int c;
    int *dev_c;                                             // khoi tao con tro dev_c o host
    HANDLE_ERROR(cudaMalloc((void **)&dev_c, sizeof(int))); // pass dia tri cua con tro dev_c vao device

    add<<<1, 1>>>(2, 7, dev_c); // pass gia tri cua dev_c (la dia chi nao do) vao add

    HANDLE_ERROR(cudaMemcpy(&c, dev_c, sizeof(int),
                            cudaMemcpyDeviceToHost)); // pass dia chi cua c, thay doi gia tri cua c = gia tri cua dev_c tro toi
    printf("2 + 7 = %d\n", c);
    HANDLE_ERROR(cudaFree(dev_c)); // xoa dev_c khoi device

    return 0;
}