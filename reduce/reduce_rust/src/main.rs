use rayon::prelude::*;
use std::env;
use std::time::Instant;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 3 {
        eprintln!("Usage: {} N t", args[0]);
        std::process::exit(1);
    }

    let n: usize = args[1].parse().expect("Invalid value for N");
    let t: usize = args[2].parse().expect("Invalid value for t");

    rayon::ThreadPoolBuilder::new()
        .num_threads(t)
        .build_global()
        .expect("Failed to build thread pool");

    let start_time = Instant::now();

    let a: Vec<f64> = (0..n).into_par_iter().map(|i| i as f64).collect();

    let sum: f64 = a.par_iter().sum();

    let duration = start_time.elapsed();

    println!("Sum = {}", sum);
    println!("Time taken: {:.6} seconds", duration.as_secs_f64());
}
