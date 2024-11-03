#include <iostream>
#include <omp.h>

using namespace std;
const int N = 10000;     // 图像的高和宽
const int n = 3;         // kernel的高和宽
const int K = N - n + 1; // output的高和宽
const int thread_num = 16;
int image[N][N];
int kernel[n][n];
int output[K][K];

int main()
{
    // int thread_count=strtol(argv[1],NULL,10);
    srand(time(NULL));
    for (int oh = 0; oh < N; oh++)
    {
        for (int ow = 0; ow < N; ow++)
        {
            image[oh][ow] = rand() % 256;
        }
    }

    for (int oh = 0; oh < n; oh++)
    {
        for (int ow = 0; ow < n; ow++)
        {
            kernel[oh][ow] = rand() % 2;
        }
    }

    // int Num=0;

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

    // cout<<"一共执行了多少次"<<Num;

    return 0;
}