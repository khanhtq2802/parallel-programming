#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int ax = 2, ay = 3, bx = 3, by = 2;
    int a[ax][ay]; 
    int b[bx][by]; 
    int c[ax][by];

    // Initialize arrays a and b
    for (int i=0;i<ax;i++)
    {
        for(int j=0;j<ay;j++)
        {
            a[i][j]=(i+1)*(j+1);
        }
    }

    for (int i=0;i<bx;i++)
    {
        for(int j=0;j<by;j++)
        {
            b[i][j]=(i+1)*(j+1);
        }
    }

    int len_domain;
    #pragma omp parallel shared(len_domain)
    {
        len_domain = ax/omp_get_num_threads();
        int threadID = omp_get_thread_num();

        int start = threadID*len_domain;
        int end = start + len_domain -1;
        if (threadID == omp_get_num_threads() - 1) end = ax - 1;


        for (int i = start; i <= end; i++)
        {
            for (int j = 0; j < by; j++)
            {
                c[i][j] = 0;
                for (int k = 0; k < ay; k++)
                {
                    c[i][j] += a[i][k]*b[k][j]; 
                }
            }
        }
    }

    // Display the result
    printf("Maxtrix A");
    for (int i=0;i<ax;i++)
    {
        printf("\n");
        for (int j=0; j<ay;j++)
        {
            printf("%d ", a[i][j]);
        }
    }
    printf("\n");

    printf("Maxtrix B");
    for (int i=0;i<bx;i++)
    {
        printf("\n");
        for (int j=0; j<by;j++)
        {
            printf("%d ", b[i][j]);
        }
    }
    printf("\n");

    printf("Maxtrix C:");
    for (int i=0;i<ax;i++)
    {
        printf("\n");
        for (int j=0; j<by;j++)
        {
            printf("%d ", c[i][j]);
        }
    }
    printf("\n");
    return 0;
}
