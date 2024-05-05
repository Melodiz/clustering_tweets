#include "KMeans.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    int NumberOfClusters = 20;
    int NumberOfIterations = 100;
    std::string pointsPath = "../data/t-SNE_projected.csv";
    std::string centroidsPath = "../data/centroids.csv";
    std::string resultPath = "../data/clustered_points.csv";

    std::cout << "Initializing kMeansClustering..." << std::endl;
    KMeans kmeans(NumberOfClusters, NumberOfIterations, pointsPath, centroidsPath, resultPath);
    // time measurement
    auto start = std::chrono::steady_clock::now();

    std::cout << "Processing..." << std::endl;
    kmeans.run();

    std::cout << "-------------Done-------------" << std::endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time taken by kMeansClustering: " << elapsed_seconds.count() << " seconds" << std::endl;

    return 0;
}