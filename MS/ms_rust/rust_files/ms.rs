use rand::Rng;
use rayon::prelude::*;
use std::env;

const N: usize = 10_000_000;
fn merge(left_arr: &[i32], right_arr: &[i32], helper: &mut [i32]) {
    let (mut l_pointer, mut r_pointer, mut helper_pointer) = (0, 0, 0);
    while l_pointer < left_arr.len() && r_pointer < right_arr.len() {
        if left_arr[l_pointer] <= right_arr[r_pointer] {
            helper[helper_pointer] = left_arr[l_pointer];
            l_pointer += 1;
        } else {
            helper[helper_pointer] = right_arr[r_pointer];
            r_pointer += 1;
        }
        helper_pointer += 1;
    }
    while l_pointer < left_arr.len() {
        helper[helper_pointer] = left_arr[l_pointer];
        l_pointer += 1;
        helper_pointer += 1;
    }
    while r_pointer < right_arr.len() {
        helper[helper_pointer] = right_arr[r_pointer];
        r_pointer += 1;
        helper_pointer += 1;
    }
}

fn merge_sort(arr: &mut [i32], depth: usize, max_depth: usize) {
    let len = arr.len();
    if len > 1 {
        let mid = len / 2;
        if depth < max_depth {
            let (left, right) = arr.split_at_mut(mid);
            rayon::join(
                || merge_sort(left, depth + 1, max_depth),
                || merge_sort(right, depth + 1, max_depth),
            );
        } else {
            merge_sort(&mut arr[..mid], depth + 1, max_depth);
            merge_sort(&mut arr[mid..], depth + 1, max_depth);
        }
        let mut helper = arr.to_vec();
        merge(&arr[..mid], &arr[mid..], &mut helper);
        arr.copy_from_slice(&helper);
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        eprintln!("max recursion depth required");
        std::process::exit(1);
    }
    let max_depth: usize = args[1].parse().expect("Invalid max depth");
    let mut arr: Vec<i32> = (0..N)
        .map(|_| rand::thread_rng().gen_range(0..100_000))
        .collect();
    // println!("Before sorting: {:#?}", arr);
    merge_sort(&mut arr, 0, max_depth);
    // println!("After sorting: {:#?}", arr);
}
