```shell
# @author Qian Zhang

g++ -Wall -fopenmp -o ms ms.omp.cpp
time ./ms 100000000 4 # ./ms [max_depth]
```
