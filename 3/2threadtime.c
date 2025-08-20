#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Macro for 2D indexing in 1D array
#define IDX(i, j, n) ((i) * (n) + (j))

// Fill matrices with simple values
void fill_matrix(double *A, double *B, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[IDX(i, j, n)] = i + j;   // Example: A(i,j) = i+j
            B[IDX(i, j, n)] = i - j;   // Example: B(i,j) = i-j
        }
    }
}

// Matrix addition using OpenMP
void add_matrix(double *A, double *B, double *C, int n) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[IDX(i, j, n)] = A[IDX(i, j, n)] + B[IDX(i, j, n)];
        }
    }
}

int main() {
    // Different matrix sizes
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    // Different thread counts
    int threads[] = {1, 2, 4, 8};
    int num_threads = sizeof(threads) / sizeof(threads[0]);

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        printf("\nMatrix Size: %d x %d\n", n, n);

        // Allocate matrices
        double *A = (double*) malloc(n * n * sizeof(double));
        double *B = (double*) malloc(n * n * sizeof(double));
        double *C = (double*) malloc(n * n * sizeof(double));

        if (!A || !B || !C) {
            printf("Memory allocation failed for %d\n", n);
            return 1;
        }

        // Fill input matrices
        fill_matrix(A, B, n);

        double base_time = 0.0;

        // Run with different thread counts
        for (int t = 0; t < num_threads; t++) {
            omp_set_num_threads(threads[t]);

            double start = omp_get_wtime();
            add_matrix(A, B, C, n);
            double end = omp_get_wtime();

            double elapsed = end - start;
            if (threads[t] == 1) base_time = elapsed;

            double speedup = base_time / elapsed;

            printf("Threads: %d, Time: %.6f sec, Speedup: %.2f\n",
                   threads[t], elapsed, speedup);
        }

        free(A);
        free(B);
        free(C);
    }

    return 0;
}