use rayon::prelude::*;
use rand::Rng;
use std::env;
use std::time::Instant;

fn initialize_matrix(rows: usize, cols: usize) -> Vec<f64> {
    let mut rng = rand::thread_rng();
    (0..rows * cols)
        .map(|_| rng.gen::<f64>())
        .collect()
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 5 {
        eprintln!("Usage: {} M N K t", args[0]);
        std::process::exit(1);
    }

    let m: usize = args[1].parse().expect("Invalid value for M");
    let n: usize = args[2].parse().expect("Invalid value for N");
    let k: usize = args[3].parse().expect("Invalid value for K");
    let t: usize = args[4].parse().expect("Invalid value for t");

    rayon::ThreadPoolBuilder::new()
        .num_threads(t)
        .build_global()
        .expect("Failed to build thread pool");

    let a = initialize_matrix(m, n);
    let b = initialize_matrix(n, k);

    let start_time = Instant::now();

    let c = multiply_matrices(&a, &b, m, n, k);

    let duration = start_time.elapsed();

    println!("Time taken: {:.6} seconds", duration.as_secs_f64());

    // print_matrix(&c, m, k);
}

fn multiply_matrices(a: &Vec<f64>, b: &Vec<f64>, m: usize, n: usize, k: usize) -> Vec<f64> {
    let b_transposed = transpose_matrix(b, n, k);

    let mut c = vec![0.0; m * k];

    c.par_chunks_mut(k)
        .enumerate()
        .for_each(|(i, row_c)| {
            let row_a = &a[i * n..(i + 1) * n];
            for j in 0..k {
                let col_b = &b_transposed[j * n..(j + 1) * n];
                row_c[j] = dot_product(row_a, col_b);
            }
        });

    c
}

fn dot_product(a: &[f64], b: &[f64]) -> f64 {
    a.iter().zip(b.iter()).map(|(x, y)| x * y).sum()
}

fn transpose_matrix(matrix: &Vec<f64>, rows: usize, cols: usize) -> Vec<f64> {
    let mut transposed = vec![0.0; rows * cols];
    for i in 0..rows {
        for j in 0..cols {
            transposed[j * rows + i] = matrix[i * cols + j];
        }
    }
    transposed
}

fn print_matrix(matrix: &Vec<f64>, rows: usize, cols: usize) {
    for i in 0..rows {
        for j in 0..cols {
            print!("{:.2} ", matrix[i * cols + j]);
        }
        println!();
    }
}
