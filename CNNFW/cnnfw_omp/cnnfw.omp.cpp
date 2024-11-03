#include <iostream>
#include <omp.h>

using namespace std;
const int N = 10000;     // image size NxN
const int n = 3;         // kernel size KSxKS
const int K = N - n + 1; // output size KxK
const int thread_num = 16;
int image[N][N];
int kernel[n][n];
int output[K][K];

int main()
{
    // int thread_count=strtol(argv[1],NULL,10);
    printf("image size:%dx%d, kernel size:%dx%d, thread_number:%d\n", N, N, n, n, thread_num);

    srand(time(NULL));
    printf("create images...\n");
    for (int oh = 0; oh < N; oh++)
    {
        for (int ow = 0; ow < N; ow++)
        {
            image[oh][ow] = rand() % 256;
        }
    }

    printf("create kernels...\n");
    for (int oh = 0; oh < n; oh++)
    {
        for (int ow = 0; ow < n; ow++)
        {
            kernel[oh][ow] = rand() % 2;
        }
    }

    // int Num=0;

    printf("compute convolution...\n");
#pragma omp parallel for num_threads(thread_num)
    for (int oh = 0; oh < K; oh++)
    {
        for (int ow = 0; ow < K; ow++)
        {
            float sum = 0;

            for (int kh = 0; kh < n; kh++)
            {
                for (int kw = 0; kw < n; kw++)
                {
                    sum += image[oh + kh][ow + kw] * kernel[kh][kw];
                    // Num++;
                }
            }

            // if(bias) sum +=bias[]
            output[oh][ow] = sum;
        }
    }

    // for (int i = 0; i < K; i++)
    // {
    //     for (int j = 0; j < K; j++)
    //         cout << output[i][j] << " ";
    //     cout << endl;
    // }

    printf("completed!\n");

    return 0;
}