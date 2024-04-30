#include <algorithm>// for sorting
#include <chrono>   // for time measurement
#include <cmath>    // for pow and other math functions
#include <fstream>
#include <iostream>
#include <map>
#include <random>// for randomly initializing centroids
#include <string>
#include <utility>
#include <vector>

#include "fix_k-means2D.h"// for k-means clustering algorithm


int main()
{
    // hyper-parameters:
    int numberOfClusters = 20;
    int maxIterations = 100;

    std::string filePathTSNE = "../data/t-SNE_projected.csv";
    std::string filePathResult = "../data/TSNE_train_embeddings_clusters.csv";
    std::string filePathCentroinds = "../data/centroids.csv";

    // time measurement start
    auto start = std::chrono::high_resolution_clock::now();

    // read data
    std::vector<Point> points = read_data(filePathTSNE);

    // do the clustering and save centroids
    std::vector<Point> centroids = kMeansClustering(points, numberOfClusters, maxIterations);

    // save the result and centroids to csv

    save_centroids_to_csv(filePathCentroinds, centroids);
    save_result_to_csv(filePathResult, points, centroids);

    // end of processing
    std::cout << "-------------Done-------------" << std::endl;
    // reveal time measurement
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time taken by kMeansClustering: " << elapsed_seconds.count() << " seconds" << std::endl;
    return 0;
}
