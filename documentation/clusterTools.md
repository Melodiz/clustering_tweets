# ClusterTools Documentation

## Overview

The `ClusterTools.hpp` file contains utility functions and methods that assist in the clustering process. These tools are designed to work with the `Cluster` and `Point` classes, providing functionalities such as calculating cluster sizes, sorting clusters, and other relevant operations.

## Input Data Structure

### Point Class

The `Point` class represents a point in a multi-dimensional space. Each `Point` object contains coordinates that define its position in the space. The `Point` class also provides methods to calculate the Euclidean distance between two points and other vector operations.

### Cluster Class

The `Cluster` class represents a cluster of points. Each `Cluster` object contains:
- `cluster_id`: An integer representing the cluster ID.
- `center`: A `Point` object representing the center of the cluster.
- `points`: A vector of `Point` objects representing the points within the cluster.
- `num_points`: An integer representing the number of points in the cluster.

## Expected Output

The functions in `ClusterTools.hpp` do not return any values directly. Instead, they perform operations on the `Cluster` and `Point` objects, such as calculating sizes, sorting, and other manipulations. The expected output is the modified state of the `Cluster` and `Point` objects.

## Algorithm Idea

### Steps

1. **Initialization**: Each function initializes the necessary data structures and variables.
2. **Processing**: The functions perform the required operations on the `Cluster` and `Point` objects.
3. **Output**: The functions modify the state of the `Cluster` and `Point` objects as needed.

### Detailed Algorithm

- **returnClustersSize**: This function calculates the size of each cluster by counting the number of points in each cluster.
- **sortClusters**: This function sorts the clusters based on a specified criterion, such as the distance from the center.
- **getRelevantNeighbors**: This function finds the k-nearest neighbors of a given point within a cluster.

## Advantages of This Implementation

1. **Modularity**: The functions in `ClusterTools.hpp` are modular and can be easily reused in different parts of the project.
2. **Efficiency**: The functions are designed to be efficient, minimizing the computational overhead.
3. **Flexibility**: The functions can handle clusters and points in multi-dimensional spaces, making them versatile for various applications.
4. **Ease of Use**: The functions provide intuitive and easy-to-use interfaces for common clustering operations.

## Example Usage

### returnClustersSize

```cpp
std::map<int, int> clusterSizes = returnClustersSize(points);
```

### sortClusters

```cpp
sortClusters(clusters);
```

### getRelevantNeighbors

```cpp
std::vector<Point> neighbors = getRelevantNeighbors(point, cluster, k);
```

## Conclusion

The `ClusterTools.hpp` file provides essential utility functions for working with clusters and points in multi-dimensional spaces. These functions enhance the modularity, efficiency, and flexibility of the clustering process, making it easier to perform common operations on clusters and points.