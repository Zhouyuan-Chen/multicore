use rayon::prelude::*;
use rand::Rng;
use std::time::SystemTime;

const N: usize = 10000; // image size NxN
const KERNEL_SIZE: usize = 3; // kernel size KSxKS
const K: usize = N - KERNEL_SIZE + 1; // output size KxK
const THREAD_NUM: usize = 16; // thread number

fn main() {
    let mut rng = rand::thread_rng();

    let mut image = vec![vec![0; N]; N];
    let mut kernel = vec![vec![0; KERNEL_SIZE]; KERNEL_SIZE];
    let mut output = vec![vec![0; K]; K];

    
    println!("image size:{}x{}, kernel size:{}x{}, thread_number:{}",N,N,KERNEL_SIZE,KERNEL_SIZE,THREAD_NUM);
    println!("create images...");
    // create images
    for row in image.iter_mut() {
        for pixel in row.iter_mut() {
            *pixel = rng.gen_range(0..256);
        }
    }

    println!("create kernels...");
    // create kernels
    for row in kernel.iter_mut() {
        for value in row.iter_mut() {
            *value = rng.gen_range(0..2);
        }
    }

    println!("compute convolution...");
    // compute the convolution in parallel
    output.par_iter_mut().enumerate().for_each(|(oh, row)| {
        for ow in 0..K {
            let mut sum = 0;

            for kh in 0..KERNEL_SIZE {
                for kw in 0..KERNEL_SIZE {
                    sum += image[oh + kh][ow + kw] * kernel[kh][kw];
                }
            }

            row[ow] = sum;
        }
    });

    // print the result if needed

    // for row in &output {
    //     for value in row {
    //         print!("{} ", value);
    //     }
    //     println!();
    // }

    println!("completed!");
}
