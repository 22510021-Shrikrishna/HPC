#include <stdio.h>
#include <omp.h>

#define N 100

int main() {
    int A[N][N], C[N][N];
    int scalar = 5;  // Example scalar value

    omp_set_num_threads(4);

    // Initialize matrix A
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            A[i][j] = i;
            C[i][j] = 0;
        }
    }

    double start_time = omp_get_wtime();

    // Scalar multiplication using OpenMP
    #pragma omp parallel for collapse(2)
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            C[i][j] = scalar * A[i][j];
        }
    }

    double end_time = omp_get_wtime();

    printf("Scalar multiplication completed.\n");
    printf("Time taken: %f seconds\n", end_time - start_time);
    printf("C[0][0] = %d, C[0][1] = %d, C[1][0] = %d\n", C[0][0], C[0][1], C[1][0]);

    return 0;
}
