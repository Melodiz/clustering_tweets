#include "KMeans.h"
#include <iostream>
#include <string>
#include <vector>

// int _k;       // store the number of clusters
// int _max_iter;// store the maximum number of iterations

// // store centroids
// // i-th element store the coordinates of i-th centroid
// std::vector<Point> _centroids;

// // store file paths
// std::string _pointsPath;   // store the path of the file with row points
// std::string _centroidsPath;// store the path of the file to write centroids
// std::string _resultPath;   // store the path of the file to write result

// // store points
// std::vector<Point> _points;// store all points
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
    // auto start = std::chrono::steady_clock::now();

    std::cout << "Processing..." << std::endl;
    kmeans.run();

    std::cout << "-------------Done-------------" << std::endl;

    // auto end = std::chrono::steady_clock::now();
    // std::chrono::duration<double> elapsed_seconds = end - start;
    // std::cout << "Time taken by kMeansClustering: " << elapsed_seconds.count() << " seconds" << std::endl;
    return 0;
}