```shell
# @author Zhouyuan Chen
# you can change the global parameters in the cpp file

gcc -Wall -fopenmp -o cnn mc.omp.cpp
time ./cnn
```