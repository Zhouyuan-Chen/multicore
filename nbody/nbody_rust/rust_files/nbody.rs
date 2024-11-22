use rayon::prelude::*;
use std::f64;
use rand::Rng;
use std::env;
use std::process;

#[derive(Clone, Copy)]
struct Particle {
    x: f64,
    y: f64,
    z: f64,
    vx: f64,
    vy: f64,
    vz: f64,
    mass: f64,
}

fn configure_rayons_thread_pool(threads: usize) {
    rayon::ThreadPoolBuilder::new()
        .num_threads(threads)
        .build_global()
        .unwrap_or_else(|e| {
            eprintln!("Error configuring Rayon thread pool: {}", e);
            process::exit(1);
        });
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let mut n: usize = 10000; 
    let mut steps: usize = 1000; 
    let mut threads: usize = 4;
    if args.len() >= 2 {
        n = args[1].parse().expect("Invalid number of particles");
        steps = args[2].parse().expect("Invalid number of steps");
        threads = args[3].parse().expect("Invalid number of threads");
    }
    let custom_pool = match rayon::ThreadPoolBuilder::new().num_threads(threads).build() {
        Ok(pool) => pool,
        Err(e) => {
            eprintln!("Error creating custom Rayon thread pool: {}", e);
            process::exit(1);
        }
    };

    let g: f64 = 6.67430e-11;
    let dt: f64 = 0.01;
    let softening: f64 = 1.0e-5;

    // Initialize particles
    let particles: Vec<Particle> = (0..n).map(|_| {
        let mut rng = rand::thread_rng();
        Particle {
            x: rng.gen_range(0.0..1000.0),
            y: rng.gen_range(0.0..1000.0),
            z: rng.gen_range(0.0..1000.0),
            vx: 0.0,
            vy: 0.0,
            vz: 0.0,
            mass: 1.0e20,
        }
    }).collect();

    // Run simulation within the custom thread pool
    custom_pool.install(|| run_simulation(particles, steps, g, dt, softening));
}

fn run_simulation(particles: Vec<Particle>, steps: usize, g: f64, dt: f64, softening: f64) {
    let mut particles = particles; 
    for step in 0..steps {
        let accelerations: Vec<(f64, f64, f64)> = particles
            .par_iter()
            .enumerate()
            .map(|(i, p)| {
                let mut ax = 0.0;
                let mut ay = 0.0;
                let mut az = 0.0;
                for (j, pj) in particles.iter().enumerate() {
                    if i == j {
                        continue;
                    }
                    let dx = pj.x - p.x;
                    let dy = pj.y - p.y;
                    let dz = pj.z - p.z;
                    let dist_sqr = dx * dx + dy * dy + dz * dz + softening; 
                    let inv_dist = dist_sqr.sqrt().recip();
                    let inv_dist3 = inv_dist * inv_dist * inv_dist;
                    ax += g * pj.mass * dx * inv_dist3;
                    ay += g * pj.mass * dy * inv_dist3;
                    az += g * pj.mass * dz * inv_dist3;
                }
                (ax, ay, az)
            })
            .collect();

        particles
            .par_iter_mut()
            .zip(accelerations.par_iter())
            .for_each(|(p, (ax, ay, az))| {
                p.vx += ax * dt;
                p.vy += ay * dt;
                p.vz += az * dt;

                p.x += p.vx * dt;
                p.y += p.vy * dt;
                p.z += p.vz * dt;
            });

        // Print progress every 100 steps
        // if (step + 1) % 100 == 0 {
        //     println!("Completed step {}/{}", step + 1, steps);
        // }
    }
    println!("Simulation Completed");
}