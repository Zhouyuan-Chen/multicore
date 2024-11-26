# multicore

Multicore course project 2024 fall

Members: Changyue Su, Zhouyuan Chen, Qian Zhang, Hao Li

## Algorithm:

- MC: Monte Carlo
- CNNFW: CNN Foward
- MS: Merge Sort
- PS: Prefix Sum
- nbody: N-Body problem
- knn: k-Nearest Neighbors
- reduce: Reduce problem
- mm: Matrix Multiplication

## To compile and run:

**nbody openmp:**
- go to file: ```cd nbody/nbody_omp/```
- compile:```gcc -fopenmp -o nbody_omp nbody.c -lm```
- run(e.g. 1000 particles, 1000 steps, 8 threads): ```./nbody_omp 1000 1000 8```

**nbody rust:**
- go to file: ```cd nbody/nbody_rust/```
- compile and run:
   ```
      # install rust and cargo
      curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
      # create project folder
      cargo init nbody
      cd nbody/
      cp ../rust_files/nbody.rs ./src/main.rs
      cp ../rust_files/Cargo.toml ./Cargo.toml
     # compile
      cargo build --release
      # run 
      # example: 1000 particles, 1000 steps, 8 threads
      cargo run --release 1000 1000 8
  ```

**knn openmp:**
- go to file: ```cd knn/knn_omp/```
- compile:```gcc -fopenmp -o knn_omp knn.c -lm```
- run(e.g. 10000 training points, 1000 testing points, 8 threads): ```./nbody_omp 10000 1000 8```

**knn rust:**
- go to file: ```cd knn/knn_rust/```
- compile and run:
   ```
      # install rust and cargo
      curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
      # create project folder
      cargo init knn_rs
      cd knn_rs/
      cp ../rust_files/knn.rs ./src/main.rs
      cp ../rust_files/Cargo.toml ./Cargo.toml
      # compile
      cargo build --release
      # run 
      # example: 10000 training points, 1000 testing points, 8 threads
      cargo run --release 10000 1000 8
  ```
   
## Folder Structure:
```text
.gitignore          - this will ignore vagrant and other metadata files

nbody/                     - nbody algorithm
├── nbody_omp/             - nbody openmp
│   └── nbody.c        
└── nbody_rust/            - nbody rust
    ├── rust_files
    │   ├── nbody.rs
    │   └── Cargo.toml
    └── readme.md          - README for compile and run rust files
knn/                       - knn algorithm
├── knn_omp/               - knn openmp
│   └── knn.c        
└── knn_rust/              - knn rust
    ├── rust_files
    │   ├── knn.rs
    │   └── Cargo.toml
    └── readme.md          - README for compile and run rust files




```
