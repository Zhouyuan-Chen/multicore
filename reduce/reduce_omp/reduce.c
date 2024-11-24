#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int i, t;
    double sum = 0.0;
    int N;

    // Parse command-line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s N t\n", argv[0]);
        return -1;
    }

    N = atoi(argv[1]);
    t = atoi(argv[2]);

    // Allocate memory for the array
    double *a = (double *)malloc(N * sizeof(double));
    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return -1;
    }

    // Start timing
    double start_time = omp_get_wtime();
        
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        a[i] = i * 1.0;
    }

    // Set the number of threads for OpenMP
    omp_set_num_threads(t);

    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < N; i++) {
        sum += a[i];
    }

    // Stop timing
    double end_time = omp_get_wtime();
    double ttaken = end_time - start_time;

    free(a);

    // Print the result
    printf("Sum = %f\n", sum);
    // Print the timing information
    printf("Time taken: %f seconds\n", ttaken);

    return 0;
}
