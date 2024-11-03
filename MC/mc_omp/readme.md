```shell
# @author Zhouyuan Chen

gcc -Wall -fopenmp -o mc mc.omp.cpp
time ./mc 100000 4 # ./mc [sampling_num] [thread_num]
```