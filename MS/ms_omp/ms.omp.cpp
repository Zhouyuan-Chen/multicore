#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;
const int N = 10000000;        // array size
vector<int> unsorted_array(N); // array

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
            // parallize merge sort with low depth
#pragma omp parallel sections
            {
#pragma omp section
                merge_sort(unsorted_array, left, mid, depth + 1, max_depth);
#pragma omp section
                merge_sort(unsorted_array, mid + 1, right, depth + 1, max_depth);
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
    if (argc != 2)
    {
        fprintf(stderr, "max recursion depth required\n");
        exit(1);
    }
    int max_depth = atoi(argv[1]);
    printf("array is size of %d\n", N);
    srand(time(NULL));
    printf("generate array\n");
    for (int i = 0; i < N; ++i)
    {
        unsorted_array[i] = rand() % 100000;
    }

    // print_array(unsorted_array);
    merge_sort(unsorted_array, 0, N - 1, 0, max_depth);
    // print_array(unsorted_array);
    printf("merge sort compelete\n");
    return 0;
}