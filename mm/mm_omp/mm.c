#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Randomly initialize a matrix
void initialize_matrix(double *matrix, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        matrix[i] = (double)rand() / RAND_MAX;
    }
}

// Print matrix (for debugging)
void print_matrix(double *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int M, N, K, t;

    // Parse command-line arguments
    if (argc != 5) {
        fprintf(stderr, "Usage: %s M N K t\n", argv[0]);
        return -1;
    }

    M = atoi(argv[1]); // matrix A row
    N = atoi(argv[2]); // matrix A col, matrix B row
    K = atoi(argv[3]); // matrix B col
    t = atoi(argv[4]); // numbers of threads

    // Set the number of threads for OpenMP
    omp_set_num_threads(t);

    // Allocate memory for the matrixs
    double *A = (double *)malloc(M * N * sizeof(double));
    double *B = (double *)malloc(N * K * sizeof(double));
    double *C = (double *)malloc(M * K * sizeof(double));

    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return -1;
    }

    // Initialize random number seed
    srand(time(NULL));

    // Initialize matrix A B
    initialize_matrix(A, M, N);
    initialize_matrix(B, N, K);

    // Start timing
    double start_time = omp_get_wtime();

    // Parallel matrix multiplication
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * K + j];
            }
            C[i * K + j] = sum;
        }
    }

    // Stop timing
    double end_time = omp_get_wtime();
    double time_taken = end_time - start_time;

    // Print debuging
    /*
    printf("Matrix A:\n");
    print_matrix(A, M, N);

    printf("Matrix B:\n");
    print_matrix(B, N, K);

    printf("Matrix C:\n");
    print_matrix(C, M, K);
    */

    // 输出计算时间
    printf("Time taken: %f seconds\n", time_taken);

    // 释放内存
    free(A);
    free(B);
    free(C);

    return 0;
}
