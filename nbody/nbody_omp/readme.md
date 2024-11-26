```shell
#compile:
gcc -fopenmp -o nbody_omp nbody.c -lm
#run(e.g. 1000 particles, 1000 steps, 8 threads): 
./nbody_omp 1000 1000 8
```
