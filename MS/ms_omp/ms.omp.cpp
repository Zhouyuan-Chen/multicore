#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>
using namespace std;
int N = 100000000; // array size
double ttaken = 0.0;

void merge(vector<int> &unsorted_array, int left, int mid, int right)
{
    int left_size = mid - left + 1;
    int right_size = right - mid;
    vector<int> helper(right_size + left_size);
    int l_pointer = left;
    int r_pointer = mid + 1;
    int helper_pointer = 0;

    while (l_pointer <= mid && r_pointer <= right)
    {
        if (unsorted_array[l_pointer] <= unsorted_array[r_pointer])
        {
            helper[helper_pointer++] = unsorted_array[l_pointer++];
        }
        else
        {
            helper[helper_pointer++] = unsorted_array[r_pointer++];
        }
    }
    while (l_pointer <= mid)
    {
        helper[helper_pointer++] = unsorted_array[l_pointer++];
    }
    while (r_pointer <= right)
    {
        helper[helper_pointer++] = unsorted_array[r_pointer++];
    }
    for (int i = 0; i < right_size + left_size; ++i)
        unsorted_array[left + i] = helper[i];
}

void merge_sort(vector<int> &unsorted_array, int left, int right, int depth, int max_depth)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        if (depth < max_depth)
        {
            double tstart = omp_get_wtime();
#pragma omp parallel sections
            {
#pragma omp section
                {
                    merge_sort(unsorted_array, left, mid, depth + 1, max_depth);
                }
#pragma omp section
                {
                    merge_sort(unsorted_array, mid + 1, right, depth + 1, max_depth);
                }
            }
            double tend = omp_get_wtime();
            if (depth == 0)
            {
#pragma omp atomic
                ttaken += tend - tstart;
            }
        }
        else
        {
            merge_sort(unsorted_array, left, mid, depth + 1, max_depth);
            merge_sort(unsorted_array, mid + 1, right, depth + 1, max_depth);
        }

        merge(unsorted_array, left, mid, right);
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
        fprintf(stderr, "max recursion depth required\n");
        exit(1);
    }
    N = atoi(argv[1]);
    int max_depth = atoi(argv[2]);
    printf("array is size of %d\n", N);
    srand(time(NULL));
    vector<int> unsorted_array(N); // array
    printf("generate array\n");
    for (int i = 0; i < N; ++i)
    {
        unsorted_array[i] = rand() % 100000;
    }
    omp_set_nested(1);
    int num_threads = static_cast<int>(pow(2, max_depth));
    omp_set_num_threads(num_threads);
    // print_array(unsorted_array);
    double tstart2 = omp_get_wtime();
    merge_sort(unsorted_array, 0, N - 1, 0, max_depth);
    // print_array(unsorted_array);
    printf("%f\n", omp_get_wtime() - tstart2);
    printf("parallel time: %f\n", ttaken);
    printf("merge sort compelete\n");
    return 0;
}