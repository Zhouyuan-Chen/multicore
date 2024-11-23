#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

typedef struct {
    double* features;
    int label; 
} DataPoint;

double euclidean_distance(double* a, double* b, int dimensions) {
    double dist = 0.0;
    for(int i = 0; i < dimensions; i++) {
        double diff = a[i] - b[i];
        dist += diff * diff;
    }
    return sqrt(dist);
}

int compare(const void* a, const void* b) {
    double diff = (*(double*)a) - (*(double*)b);
    if (diff < 0) return -1;
    else if (diff > 0) return 1;
    else return 0;
}

int main(int argc, char *argv[]) {
    int num_train = 10000; 
    int num_test = 1000;   
    int num_threads = 4;
    if(argc >= 3) {
        num_train = atoi(argv[1]);
        num_test = atoi(argv[2]);
        num_threads = atoi(argv[3]);
    }
    
    int dimensions = 50;   // Number of features
    int k = 5;             // Number of neighbors

    DataPoint* training = malloc(num_train * sizeof(DataPoint));
    DataPoint* testing = malloc(num_test * sizeof(DataPoint));

    for(int i = 0; i < num_train; i++) {
        training[i].features = malloc(dimensions * sizeof(double));
        for(int j = 0; j < dimensions; j++) {
            training[i].features[j] = rand() / (double)RAND_MAX;
        }
        training[i].label = rand() % 2; 
    }

    for(int i = 0; i < num_test; i++) {
        testing[i].features = malloc(dimensions * sizeof(double));
        for(int j = 0; j < dimensions; j++) {
            testing[i].features[j] = rand() / (double)RAND_MAX;
        }
        testing[i].label = -1; 
    }

    int* predicted_labels = malloc(num_test * sizeof(int));

    #pragma omp parallel for schedule(dynamic)
    for(int i = 0; i < num_test; i++) {
        double* distances = malloc(num_train * sizeof(double));

        for(int j = 0; j < num_train; j++) {
            distances[j] = euclidean_distance(testing[i].features, training[j].features, dimensions);
        }

        qsort(distances, num_train, sizeof(double), compare);

        int votes[2] = {0, 0}; 
        for(int l = 0; l < k; l++) {
            votes[training[l].label]++;
        }

        predicted_labels[i] = (votes[0] > votes[1]) ? 0 : 1;
        free(distances);
    }

    // Output 
    for(int i = 0; i < 10; i++) {
        printf("Test Point %d: Predicted Label = %d\n", i, predicted_labels[i]);
    }

    for(int i = 0; i < num_train; i++) {
        free(training[i].features);
    }
    for(int i = 0; i < num_test; i++) {
        free(testing[i].features);
    }
    free(training);
    free(testing);
    free(predicted_labels);

    return 0;
}
