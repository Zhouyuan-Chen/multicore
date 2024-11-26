```shell
#compile:
gcc -fopenmp -o knn_omp knn.c -lm
#run(e.g. 10000 training points, 1000 testing points, 8 threads): 
./nbody_omp 10000 1000 8
```
