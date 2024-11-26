#include <iostream>
using namespace std;
const int N = 10000;
const int n = 3;
const int K = N - n + 1;
int image[N][N];
int kernel[n][n];
int output[K][K];
int main()
{
    printf("image size:%dx%d, kernel size:%dx%d\n", N, N, n, n);
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
    printf("compute convolution...\n");
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
                }
            }
            // if(bias) sum +=bias[]
            output[oh][ow] = sum;
        }
    }
    printf("completed!\n");
    return 0;
}