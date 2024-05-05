# KMeans Clustering Documentation

## Overview

The KMeans class implements the K-Means clustering algorithm, a popular method for partitioning data into K distinct, non-overlapping subsets. The algorithm iterates through two main steps: assigning points to the nearest cluster centroid and recalculating centroids based on the assignments. This process repeats until the assignments no longer change or a maximum number of iterations is reached.

## Dependencies

- C++ Standard Library
- `<algorithm>` for sorting and other algorithms.
- `<chrono>` for measuring execution time (optional).
- `<cmath>` for mathematical functions.
- `<fstream>` for file input/output operations.
- `<iostream>` for input/output streaming.
- `<map>` for storing mappings from cluster IDs to points.
- `<random>` for initializing centroids randomly.
- `<string>` for string manipulation.
- `<vector>` for storing collections of points and centroids.
- `npy.hpp` for reading `.npy` files.

## Data Structures

### Point

Represents a point in a two-dimensional space with the following properties:

- `x`: The x-coordinate of the point.
- `y`: The y-coordinate of the point.
- `distance`: The distance from the point to its assigned cluster centroid.
- `cluster_id`: The ID of the cluster to which the point is assigned.

### KMeans

Implements the K-Means clustering algorithm with the following member variables:

- `_k`: The number of clusters.
- `_max_iter`: The maximum number of iterations to run the algorithm.
- `_centroids`: A vector of points representing the centroids of the clusters.
- `_pointsPath`, `_centroidsPath`, `_resultPath`: File paths for input data, centroid output, and clustering result output, respectively.
- `_points`: A vector of points representing the data to be clustered.

## Member Functions

### Constructor

Initializes a KMeans instance with specified parameters for the number of clusters, maximum iterations, and file paths.

### `void run()`

Executes the K-Means clustering algorithm, including saving the results and centroids to CSV files.

### `void setPoints(std::vector<Point> points)`

Sets the points to be clustered and initializes random centroids.

### `std::vector<Point> getPoints()`

Returns the vector of points after clustering.

## Utility Functions

### `std::vector<Point> read_data(std::string path)`

Reads data from a specified file path. Supports `.csv`, `.npy`, and `.txt` formats.

### `std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k)`

Initializes `k` random centroids from the given points.

### `void save_result_to_csv()`

Saves the clustering result to a CSV file specified by `_resultPath`.

### `void save_centroids_to_csv()`

Saves the centroids to a CSV file specified by `_centroidsPath`.

## Algorithm Steps

1. **Initialization**: Randomly select `k` points as the initial centroids.
2. **Assignment**: Assign each point to the nearest centroid.
3. **Update**: Recalculate the centroids as the mean of all points assigned to each cluster.
4. **Repeat**: Steps 2 and 3 repeat until the assignments no longer change or the maximum number of iterations is reached.

## Usage

To use the KMeans class, create an instance with the desired parameters and call the `run` method. Ensure that the input data is prepared and accessible at the specified path. The results and centroids will be saved to the paths provided during initialization.

## Note

This documentation assumes familiarity with the K-Means clustering algorithm and basic C++ programming concepts.