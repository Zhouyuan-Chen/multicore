#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;
int N = 100000000; // array size
double tstart = 0.0, ttaken = 0.0;

void prefix_scan(vector<int> &prefix_sum, int n, int thread_count)
{
    for (int step = 1; step < n; step *= 2)
    {
        vector<int> helper(n);
        helper.assign(prefix_sum.begin(), prefix_sum.end());
        tstart = omp_get_wtime();
#pragma omp parallel for num_threads(thread_count) schedule(static)
        for (int i = step; i < n; i++)
        {
            prefix_sum[i] += helper[i - step];
        }
        ttaken = ttaken + omp_get_wtime() - tstart;
    }
}

void print_array(vector<int> &arr)
{
    for (unsigned int i = 0; i < arr.size(); i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "number of threads required\n");
        exit(1);
    }
    N = atoi(argv[1]);
    int n_threads = atoi(argv[2]);
    vector<int> arr(N);        // array
    vector<int> prefix_sum(N); // array
    printf("array is size of %d\n", N);
    srand(time(NULL));
    printf("generating array\n");
    for (int i = 0; i < N; ++i)
    {
        arr[i] = rand() % 2;
        prefix_sum[i] = arr[i];
    }
    // print_array(arr);
    prefix_scan(prefix_sum, N, n_threads);
    // print_array(prefix_sum);
    printf("parallel time %f\n", ttaken);
    return 0;
}