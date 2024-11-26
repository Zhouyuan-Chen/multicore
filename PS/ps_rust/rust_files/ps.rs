use rand::Rng;
use rayon::prelude::*;
use std::env;
use std::time::Instant;

fn prefix_scan(prefix_sum: &mut Vec<i32>, n: usize, thread_count: usize) -> f64 {
    rayon::ThreadPoolBuilder::new()
        .num_threads(thread_count)
        .build_global()
        .unwrap();
    let mut helper = prefix_sum.clone();
    let mut step = 1;
    let mut ttaken = 0.0;
    while step < n {
        helper.copy_from_slice(prefix_sum);
        let tstart = Instant::now();
        prefix_sum.par_iter_mut().enumerate().for_each(|(i, item)| {
            if i >= step {
                *item += helper[i - step];
            }
        });
        step *= 2;
        ttaken = ttaken + tstart.elapsed().as_secs_f64();
    }
    ttaken
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 3 {
        eprintln!("max recursion depth required");
        std::process::exit(1);
    }
    let N: usize = args[1].parse().expect("Invalid array size");
    let n_threads: usize = args[2].parse().expect("Invalid number of threads");
    let arr: Vec<i32> = (0..N).map(|_| rand::thread_rng().gen_range(0..2)).collect();
    let mut prefix_sum = arr.clone();
    println!("Array is size of {}", N);
    println!("Generating array");
    // println!("Array: {:?}", arr);
    // Calculate the prefix sum
    let ttaken = prefix_scan(&mut prefix_sum, N, n_threads);
    // println!("Prefix_sum: {:?}", prefix_sum);
    println!("Task Compeleted: {:?}", ttaken);
    println!("Compute prefix sum complete");
}
