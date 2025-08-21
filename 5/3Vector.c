#include <stdio.h>
#include <omp.h>

#define N 100

int main() {
    int A[N][N], x[N], y[N];

    omp_set_num_threads(4);

    // Initialize matrix A and vector x
    for(int i=0;i<N;i++){
        x[i] = i;
        y[i] = 0;
        for(int j=0;j<N;j++){
            A[i][j] = i + j;
        }
    }

    double start_time = omp_get_wtime();

    // Matrix-vector multiplication using OpenMP
    #pragma omp parallel for
    for(int i=0;i<N;i++){
        int sum = 0;
        for(int j=0;j<N;j++){
            sum += A[i][j] * x[j];
        }
        y[i] = sum;
    }

    double end_time = omp_get_wtime();

    printf("Matrix-vector multiplication completed.\n");
    printf("Time taken: %f seconds\n", end_time - start_time);
    printf("y[0] = %d, y[1] = %d, y[2] = %d\n", y[0], y[1], y[2]);

    return 0;
}
