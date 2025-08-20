#include <stdio.h>
#include <omp.h>


#define SIZE 200
#define SCALAR 5

int main() {

    omp_set_num_threads(8);

    double A[SIZE];
    int i;
    double start, end;

    // initialize array
    for (i = 0; i < SIZE; i++) {
        A[i] = i;
    }

    // ---------- static schedule ----------
    start = omp_get_wtime();
    #pragma omp parallel for schedule(static, 10)
    for (i = 0; i < SIZE; i++) {
        A[i] = A[i] + SCALAR;
    }
    end = omp_get_wtime();
    printf("Static schedule (chunk=10) time: %f sec\n", end - start);

    // reset
    for (i = 0; i < SIZE; i++) {
        A[i] = i;
    }

    // ---------- dynamic schedule ----------
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 10)
    for (i = 0; i < SIZE; i++) {
        A[i] = A[i] + SCALAR;
    }
    end = omp_get_wtime();
    printf("Dynamic schedule (chunk=10) time: %f sec\n", end - start);

    // reset
    for (i = 0; i < SIZE; i++) {
        A[i] = i;
    }

    // ---------- nowait example ----------
    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (i = 0; i < SIZE; i++) {
            A[i] = A[i] + SCALAR;
        }

        #pragma omp single
        {
            printf("nowait function\n");
        }
    }
    end = omp_get_wtime();
    printf("Nowait example time: %f sec\n", end - start);

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <omp.h>

// #define SIZE 100000000   // 100 million
// #define SCALAR 5

// int main() {
//     omp_set_num_threads(8);  // use 8 threads

//     // allocate memory on heap
//     int *A = (int*) malloc(SIZE * sizeof(int));
//     if (A == NULL) {
//         printf("Memory allocation failed!\n");
//         return 1;
//     }

//     int i;
//     double start, end;

//     // ---------- Sequential baseline ----------
//     for (i = 0; i < SIZE; i++) {
//         A[i] = i;
//     }
//     start = omp_get_wtime();
//     for (i = 0; i < SIZE; i++) {
//         A[i] = A[i] + SCALAR;
//     }
//     end = omp_get_wtime();
//     printf("Sequential time: %.6f sec\n", end - start);

//     // reset array
//     for (i = 0; i < SIZE; i++) {
//         A[i] = i;
//     }

//     // ---------- Static schedule ----------
//     start = omp_get_wtime();
//     #pragma omp parallel for schedule(static, 1000)
//     for (i = 0; i < SIZE; i++) {
//         A[i] = A[i] + SCALAR;
//     }
//     end = omp_get_wtime();
//     printf("Static schedule (chunk=1000) time: %.6f sec\n", end - start);

//     // reset array
//     for (i = 0; i < SIZE; i++) {
//         A[i] = i;
//     }

//     // ---------- Dynamic schedule ----------
//     start = omp_get_wtime();
//     #pragma omp parallel for schedule(dynamic, 1000)
//     for (i = 0; i < SIZE; i++) {
//         A[i] = A[i] + SCALAR;
//     }
//     end = omp_get_wtime();
//     printf("Dynamic schedule (chunk=1000) time: %.6f sec\n", end - start);

//     // reset array
//     for (i = 0; i < SIZE; i++) {
//         A[i] = i;
//     }

//     // ---------- Nowait example ----------
//     start = omp_get_wtime();
//     #pragma omp parallel
//     {
//         #pragma omp for nowait
//         for (i = 0; i < SIZE; i++) {
//             A[i] = A[i] + SCALAR;
//         }

//         #pragma omp single
//         {
//             printf("Nowait: threads did not wait after for-loop\n");
//         }
//     }
//     end = omp_get_wtime();
//     printf("Nowait example time: %.6f sec\n", end - start);

//     // free memory
//     free(A);

//     return 0;
// }
