### KMeansND Class Documentation

#### Overview

The `KMeansND` class implements the K-Means clustering algorithm for N-dimensional data points. It is designed to cluster a given set of points into `k` clusters, where `k` is a parameter specified by the user. The class supports reading data from CSV, NPY, and TXT files and writing the clustering results and centroids to the same formats.

#### Constructors

- `KMeansND(int k, int max_iter, std::string pointsPath, std::string centroidsPath, std::string resultPath)`: Initializes the KMeansND object with the specified number of clusters (`k`), maximum iterations (`max_iter`), and paths for input points, output centroids, and results.
- `KMeansND(int k, int max_iter, std::vector<Point> points)`: Initializes the KMeansND object with the specified number of clusters, maximum iterations, and a vector of points.
- `KMeansND(int k, int max_iter)`: Initializes the KMeansND object with the specified number of clusters and maximum iterations, without specifying data paths or points initially.

#### Public Methods

- `void run()`: Executes the K-Means clustering algorithm, saves the results, and centroids to the specified paths.
- `void setPoints(std::vector<Point> points)`: Sets the points to be clustered.
- `std::vector<Point> getPoints()`: Returns the points that are being clustered.
- `std::vector<Point> getCentroids()`: Returns the centroids of the clusters.
- `void setCentroids(std::vector<Point> centroids)`: Sets the centroids manually.
- `void setMaxIter(int max_iter)`: Sets the maximum number of iterations for the clustering algorithm.
- `void setPointsPath(std::string pointsPath)`: Sets the path for the input points file.
- `void setCentroidsPath(std::string centroidsPath)`: Sets the path for the output centroids file.
- `void setResultPath(std::string resultPath)`: Sets the path for the output results file.
- `void setWithCoordinates(bool with_coordinates)`: Specifies whether to include coordinates in the output file.
- `void setK(int k)`: Sets the number of clusters.
- `std::map<int, int> getClustersSize()`: Returns a map where the keys are cluster IDs and the values are the sizes of the clusters.

#### Protected Methods

- `void kMeansClustering()`: The core method that performs the K-Means clustering algorithm.
- `int assignPointsToClusters()`: Assigns each point to the nearest cluster and returns the number of points that changed clusters.
- `void recalculateCentroids()`: Recalculates the centroids of the clusters based on the current cluster assignments.
- `void save_result()`: Saves the clustering results to the specified path.
- `void save_centroids()`: Saves the centroids to the specified path.

#### Utility Functions

- `std::vector<Point> read_data(std::string path)`: Reads data from the specified path and returns a vector of points.
- `std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k)`: Initializes `k` random centroids from the given points.

#### Structs

- `Point`: Represents an N-dimensional point with coordinates, distance from centroid, and cluster ID.

#### Dependencies

- `<vector>`, `<string>`, `<map>`, `<fstream>`, `<iostream>`, `<cmath>`, `<algorithm>`, `<chrono>`, `<random>`, and `"include/npy.hpp"` for NPY file handling.

#### Notes

- The class is designed to be flexible, allowing for initialization with data paths or directly with a vector of points.
- The algorithm supports outputting results with or without point coordinates, based on the `_with_coordinates` flag.
- The class checks for file types based on extensions and supports `.csv`, `.npy`, and `.txt` formats for both input and output.
