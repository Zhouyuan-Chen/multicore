#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define M_PIl 3.141592653589793238462643383279502884L

void mc_sampling(int64_t sampling_num, int64_t *accepted_sampling_num)
{
    int64_t local_accepted = 0;
    double x, y;
    for (int64_t i = 0; i < sampling_num; i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0)
        {
            local_accepted++;
        }
    }
    *accepted_sampling_num += local_accepted;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "hint: ./prog [sampling_num] [thread_num]\n");
        exit(1);
    }

    int64_t sampling_num = atoll(argv[1]);
    int thread_num = atoi(argv[2]);

    int64_t accepted_sampling_num = 0;
    int64_t sampling_num_each_thread = sampling_num / thread_num;

    for (int64_t i = 0; i < sampling_num; i++)
    {
        mc_sampling(sampling_num_each_thread, &accepted_sampling_num);
    }

    double pi = 4.0 * accepted_sampling_num / sampling_num;
    double error = fabs(pi - M_PIl) / M_PIl;

    printf("Estimated PI: %.15lf, Error: %.15lf\n", pi, error);

    return 0;
}
