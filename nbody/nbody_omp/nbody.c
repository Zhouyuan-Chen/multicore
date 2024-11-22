#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

typedef struct {
    double x, y, z;
    double vx, vy, vz;
    double mass;
} Particle;

int main(int argc, char *argv[]) {
    // Number of particles
    int N = 10000; 
    if(argc >= 3) N = atoi(argv[1]);
    int steps = 1000; 
    if(argc >= 3) steps = atoi(argv[2]);
    int num_threads = 4;
    if(argc >= 3) num_threads = atoi(argv[3]);

    double G = 6.67430e-11;
    double dt = 0.01;
    double soft_factor = 1e-10;

    omp_set_num_threads(num_threads);

    // Allocate memory for particles
    Particle *particles = malloc(N * sizeof(Particle));
    for(int i = 0; i < N; i++) {
        particles[i].x = rand() / (double)RAND_MAX * 1000.0;
        particles[i].y = rand() / (double)RAND_MAX * 1000.0;
        particles[i].z = rand() / (double)RAND_MAX * 1000.0;
        particles[i].vx = particles[i].vy = particles[i].vz = 0.0;
        particles[i].mass = 1.0e20;
    }

    
    for(int step = 0; step < steps; step++) {
      
        #pragma omp parallel for schedule(dynamic)
        for(int i = 0; i < N; i++) {
            double ax = 0.0, ay = 0.0, az = 0.0;
            for(int j = 0; j < N; j++) {
                if(i == j) continue;
                double dx = particles[j].x - particles[i].x;
                double dy = particles[j].y - particles[i].y;
                double dz = particles[j].z - particles[i].z;
                double dist_sqr = dx*dx + dy*dy + dz*dz + soft_factor; 

                double inv_dist = 1.0 / sqrt(dist_sqr);
                double inv_dist3 = inv_dist * inv_dist * inv_dist;
                ax += G * particles[j].mass * dx * inv_dist3;
                ay += G * particles[j].mass * dy * inv_dist3;
                az += G * particles[j].mass * dz * inv_dist3;
            }
            particles[i].vx += ax * dt;
            particles[i].vy += ay * dt;
            particles[i].vz += az * dt;
        }

        
        #pragma omp parallel for
        for(int i = 0; i < N; i++) {
            particles[i].x += particles[i].vx * dt;
            particles[i].y += particles[i].vy * dt;
            particles[i].z += particles[i].vz * dt;
        }

    }

    free(particles);
    return 0;
}
