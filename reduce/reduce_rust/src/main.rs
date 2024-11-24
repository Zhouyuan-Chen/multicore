use rayon::prelude::*;
use std::env;
use std::time::Instant;

fn main() {
    // 解析命令行参数
    let args: Vec<String> = env::args().collect();
    if args.len() != 3 {
        eprintln!("Usage: {} N t", args[0]);
        std::process::exit(1);
    }

    let n: usize = args[1].parse().expect("Invalid value for N");
    let t: usize = args[2].parse().expect("Invalid value for t");

    // 设置线程数
    rayon::ThreadPoolBuilder::new()
        .num_threads(t)
        .build_global()
        .expect("Failed to build thread pool");

    // 开始计时
    let start_time = Instant::now();

    // 初始化数组
    let a: Vec<f64> = (0..n).into_par_iter().map(|i| i as f64).collect();

    // 并行求和
    let sum: f64 = a.par_iter().sum();

    // 停止计时
    let duration = start_time.elapsed();

    // 打印结果
    println!("Sum = {}", sum);
    println!("Time taken: {:.6} seconds", duration.as_secs_f64());
}
