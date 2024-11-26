use rand::Rng;
use std::time::SystemTime;
const N: usize = 10000; // image size NxN
const KERNEL_SIZE: usize = 3; // kernel size KSxKS
const K: usize = N - KERNEL_SIZE + 1; // output size KxK
fn main() {
    let mut rng = rand::thread_rng();
    let mut image = vec![vec![0; N]; N];
    let mut kernel = vec![vec![0; KERNEL_SIZE]; KERNEL_SIZE];
    println!(
        "image size:{}x{}, kernel size:{}x{},",
        N, N, KERNEL_SIZE, KERNEL_SIZE
    );
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
    // Perform convolution serially
    let mut output = vec![vec![0; K]; K];
    for oh in 0..K {
        for ow in 0..K {
            let mut sum = 0;
            for kh in 0..KERNEL_SIZE {
                for kw in 0..KERNEL_SIZE {
                    sum += image[oh + kh][ow + kw] * kernel[kh][kw];
                }
            }
            output[oh][ow] = sum;
        }
    }
    println!("completed!");
}