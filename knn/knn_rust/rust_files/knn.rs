use rayon::prelude::*;
use rayon::ThreadPoolBuilder;
use std::cmp::Ordering;
use std::env;
use std::process;

#[derive(Clone, Debug)]
struct DataPoint {
    features: Vec<f64>,
    label: i32, 
}

fn euclidean_distance(a: &Vec<f64>, b: &Vec<f64>) -> f64 {
    a.iter()
        .zip(b.iter())
        .map(|(x, y)| (x - y).powi(2))
        .sum::<f64>()
        .sqrt()
}

fn knn_classify(test_point: &DataPoint, training: &[DataPoint], k: usize) -> i32 {
    let mut distances: Vec<(f64, i32)> = training
        .par_iter()
        .map(|train_point| {
            let dist = euclidean_distance(&test_point.features, &train_point.features);
            (dist, train_point.label)
        })
        .collect();

    //distances.select_nth_unstable(k);
    let k = if k > distances.len() { distances.len() } else { k };
    distances.select_nth_unstable_by(k, |a: &(f64, i32), b: &(f64, i32)| {
        a.0.partial_cmp(&b.0).unwrap_or(Ordering::Equal)
    });
    distances.truncate(k);

    let mut votes = std::collections::HashMap::new();
    for &(_, label) in distances.iter() {
        *votes.entry(label).or_insert(0) += 1;
    }

    votes.into_iter()
        .max_by(|a, b| a.1.cmp(&b.1))
        .map(|(label, _)| label)
        .unwrap_or(-1)
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let program_name = &args[0];

    let mut num_train = 10000; 
    let mut num_test = 1000; 
    let mut num_threads = rayon::current_num_threads();

    // Parse command-line arguments
    if args.len() > 1 {
        num_train = match args[1].parse() {
            Ok(n) => n,
            Err(_) => {
                eprintln!("Usage: {} [num_train] [num_test] [num_threads]", program_name);
                process::exit(1);
            }
        };
        num_test = match args[2].parse() {
            Ok(n) => n,
            Err(_) => {
                eprintln!("Usage: {} [num_test] [num_threads]", program_name);
                process::exit(1);
            }
        };
        num_threads = match args[3].parse() {
            Ok(n) => n,
            Err(_) => {
                eprintln!("Usage: {} [num_threads]", program_name);
                process::exit(1);
            }
        };
    }

    let custom_pool = match ThreadPoolBuilder::new().num_threads(num_threads).build() {
        Ok(pool) => pool,
        Err(e) => {
            eprintln!("Error creating Rayon thread pool: {}", e);
            process::exit(1);
        }
    };

    // println!("Rayon thread pool set to {} threads.", num_threads);
    // println!("Initializing datasets...");

    let dimensions = 50;  
    let k = 5;             

    let training: Vec<DataPoint> = (0..num_train)
        .map(|_| {
            let features: Vec<f64> = (0..dimensions)
                .map(|_| rand::random::<f64>())
                .collect();
            let label = rand::random::<bool>() as i32; // Binary classification: 0 or 1
            DataPoint { features, label }
        })
        .collect();

    let testing: Vec<DataPoint> = (0..num_test)
        .map(|_| {
            let features: Vec<f64> = (0..dimensions)
                .map(|_| rand::random::<f64>())
                .collect();
            DataPoint { features, label: -1 } // Unknown label
        })
        .collect();

    // println!("Datasets initialized.");
    // println!("Performing k-NN classification...");

    let predicted_labels: Vec<i32> = custom_pool.install(|| {
        testing
            .par_iter()
            .map(|test_point| knn_classify(test_point, &training, k))
            .collect()
    });

    // println!("k-NN classification completed.");
    // println!("Displaying first 10 predictions:");

    // Output the first 10 predicted labels
    for (i, label) in predicted_labels.iter().take(10).enumerate() {
        println!("Test Point {}: Predicted Label = {}", i, label);
    }
}
