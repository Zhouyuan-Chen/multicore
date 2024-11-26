```shell
# @author Qian Zhang

g++ -Wall -fopenmp -o ps ps.omp.cpp
time ./ps 100000000 4 # ./ps [array size] [num_threads]
```
