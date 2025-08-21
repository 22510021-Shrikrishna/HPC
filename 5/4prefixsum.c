#include <stdio.h>
#include <omp.h>

#define N 10

int main() {
    int A[N], B[N];

    omp_set_num_threads(4);

    // Initialize array
    for(int i=0;i<N;i++){
        A[i] = i + 1;
        B[i] = 0;
    }

    double start_time = omp_get_wtime();

    // Prefix sum using OpenMP (simple approach)
    B[0] = A[0];
    for(int i=1;i<N;i++){
        #pragma omp parallel for
        for(int j=i;j<i+1;j++){
            B[j] = B[j-1] + A[j];
        }
    }

    double end_time = omp_get_wtime();

    printf("Prefix sum completed.\n");
    printf("Time taken: %f seconds\n", end_time - start_time);
    printf("Array: ");
    for(int i=0;i<N;i++){
        printf("%d ", B[i]);
    }
    printf("\n");

    return 0;
}
