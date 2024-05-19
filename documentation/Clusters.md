# Cluster Class Documentation

## Overview

The `Cluster` class is designed to represent a cluster of points in a multi-dimensional space. It encapsulates the properties and behaviors of a cluster, including its ID, center, points, and the number of points. The class provides methods for initializing clusters, accessing cluster properties, sorting points within a cluster, and finding the nearest neighbors to the cluster center.

## Class Definition

### Header File: `Clusters.hpp`

```cpp
#pragma once
#include "../clustering_core/modules/structPoint.hpp"
#include "modules/SortingClusters.hpp"
#include "modules/ClusterRelevantInfo.hpp"
#include <string>
#include <vector>

class Cluster;

typedef std::vector<Cluster> Clusters;

class Cluster
{
public:
    Cluster() : cluster_id(-1), num_points(0) {}
    Cluster(int id) : cluster_id(id), num_points(0) {}
    Cluster(int id, const Point& center) : cluster_id(id), center(center), num_points(0) {}
    Cluster(int id, const std::vector<Point>& points) : cluster_id(id), points(points), num_points(points.size()) {}
    Cluster(int id, const Point& center, const std::vector<Point>& points) : cluster_id(id), center(center), points(points), num_points(points.size()) {}
    Cluster(int id, const Point& center, const std::vector<Point>& points, int num_points) : cluster_id(id), center(center), points(points), num_points(num_points) {}

    int getClusterId() const { return cluster_id; }
    int getNumPoints() const { return num_points; }
    const Point& getCenter() const { return center; }
    const std::vector<Point>& getPoints() const { return points; }

    void sort() { sortPointsByDistance(center, points); }

    std::vector<Point> getNeighbors(int k) const { return ::getNeighbors(center, points, k); }

protected:
    int cluster_id;
    Point center;
    std::vector<Point> points;
    int num_points;
};
```

## Input Data Structure

### Point Class

The `Point` class represents a point in a multi-dimensional space. Each `Point` object contains coordinates that define its position in the space.

### Cluster Class

- **cluster_id**: An integer representing the unique identifier of the cluster.
- **center**: A `Point` object representing the center of the cluster.
- **points**: A vector of `Point` objects representing the points that belong to the cluster.
- **num_points**: An integer representing the number of points in the cluster.

## Expected Output

The `Cluster` class provides methods to:

1. **Get the Cluster ID**: Returns the unique identifier of the cluster.
2. **Get the Number of Points**: Returns the number of points in the cluster.
3. **Get the Center**: Returns the center point of the cluster.
4. **Get the Points**: Returns the vector of points belonging to the cluster.
5. **Sort Points**: Sorts the points within the cluster by their distance from the center.
6. **Get Neighbors**: Returns the nearest neighbors to the center point within the cluster.

## Algorithm Idea

### Sorting Points

The `sort` method sorts the points within the cluster by their distance from the center. This is achieved using the `sortPointsByDistance` function, which takes the center point and the vector of points as input and sorts the points based on their Euclidean distance from the center.

### Finding Neighbors

The `getNeighbors` method returns the nearest neighbors to the center point within the cluster. This is achieved using the `getNeighbors` function, which takes the center point, the vector of points, and the number of neighbors `k` as input and returns the `k` nearest points to the center.

## Advantages of This Implementation

1. **Modularity**: The `Cluster` class is designed to be modular, with clear separation of concerns. Each method is responsible for a specific functionality, making the code easier to understand and maintain.
2. **Flexibility**: The class provides multiple constructors to initialize clusters in different ways, offering flexibility in how clusters are created and managed.
3. **Efficiency**: The sorting and neighbor-finding algorithms are designed to be efficient, leveraging the properties of the `Point` class and standard library functions.
4. **Reusability**: The `Cluster` class can be easily reused in different contexts where clustering of points in multi-dimensional space is required.
5. **Scalability**: The class is designed to handle clusters with a large number of points, making it suitable for large-scale data analysis and clustering tasks.

## Conclusion

The `Cluster` class provides a robust and flexible implementation for representing and managing clusters of points in a multi-dimensional space. With its modular design and efficient algorithms, it is well-suited for a wide range of clustering applications.