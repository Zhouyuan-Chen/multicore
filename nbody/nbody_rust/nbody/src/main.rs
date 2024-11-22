use rayon::prelude::*;
use std::f64;
use rand::Rng;

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

fn main() {
    let n: usize = 10000; // Number of particles
    let steps: usize = 1000; // Number of simulation steps
    let g: f64 = 6.67430e-11;
    let dt: f64 = 0.01;

    // Initialize particles
    let mut particles: Vec<Particle> = (0..n).map(|_| {
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

    // Simulation loop
    for _ in 0..steps {
        // Clone particles for parallel iteration to avoid mutable aliasing
        let particles_clone = particles.clone();

        // Compute accelerations in parallel
        let accelerations: Vec<(f64, f64, f64)> = particles.par_iter().enumerate().map(|(i, p)| {
            let mut ax = 0.0;
            let mut ay = 0.0;
            let mut az = 0.0;
            for (j, pj) in particles_clone.iter().enumerate() {
                if i == j { continue; }
                let dx = pj.x - p.x;
                let dy = pj.y - p.y;
                let dz = pj.z - p.z;
                let dist_sqr = dx*dx + dy*dy + dz*dz + 1e-10; // Softening factor
                let inv_dist = dist_sqr.sqrt().recip();
                let inv_dist3 = inv_dist * inv_dist * inv_dist;
                ax += g * pj.mass * dx * inv_dist3;
                ay += g * pj.mass * dy * inv_dist3;
                az += g * pj.mass * dz * inv_dist3;
            }
            (ax, ay, az)
        }).collect();

        // Update velocities and positions in parallel
        particles.par_iter_mut().zip(accelerations.par_iter()).for_each(|(p, (ax, ay, az))| {
            p.vx += ax * dt;
            p.vy += ay * dt;
            p.vz += az * dt;

            p.x += p.vx * dt;
            p.y += p.vy * dt;
            p.z += p.vz * dt;
        });
    }
}
