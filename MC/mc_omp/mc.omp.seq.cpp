#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PIl 3.141592653589793238462643383279502884L

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "hint: ./prog [sampling_num]\n");
        exit(1);
    }

    int64_t sampling_num = atoll(argv[1]);

    int64_t accepted_sampling_num = 0;
    for (int64_t i = 0; i < sampling_num; i++)
    {
        double x, y;
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0)
        {
            accepted_sampling_num++;
        }
    }

    double pi = 4.0 * accepted_sampling_num / sampling_num;
    double error = fabs(pi - M_PIl) / M_PIl;

    printf("Estimated PI: %.15lf, Error: %.15lf\n", pi, error);

    return 0;
}
