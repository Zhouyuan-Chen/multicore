# multicore

Multicore course project 2024 fall

Members: Changyue Su, Zhouyuan Chen, Qian Zhang, Hao Li

Algorithm:

- MC: Monte Carlo
- CNNFW: CNN Foward
- MS: Merge Sort
- PS: Prefix Sum
- nbody: N-Body problem
- knn: k-Nearest Neighbors
- reduce: Reduce problem
- mm: Matrix Multiplication

To compile and run:

nbody:
- compile: gcc -fopenmp -o nbody_omp nbody.c -lm
- run(e.g. 1000 particles, 1000 steps, 8 threads): ./nbody_omp 1000 1000 8 
