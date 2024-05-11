# K-Means Clustering Algorithm

The K-Means clustering algorithm is a method used to partition `n` observations into `k` clusters in which each observation belongs to the cluster with the nearest mean. This results in a partitioning of the data space into Voronoi cells. K-Means is a simple and widely-used clustering algorithm that can yield remarkable results with a relatively simple concept.

## Overview

The algorithm iterates through two main steps to partition the data:

1. **Assignment Step:** Each point (observation) is assigned to the nearest cluster center. The "nearest" is determined based on the distance metric, typically the Euclidean distance.
2. **Update Step:** The centroids (cluster centers) are recalculated as the mean of all points assigned to the respective cluster.

These steps are repeated until the algorithm converges, meaning the assignments no longer change or the maximum number of iterations is reached.

## Functions and Their Roles

### `initialize_random_centroids`

- **Purpose:** Initializes the centroids randomly from the dataset.
- **Parameters:**
  - `const std::vector<Point>& points`: The dataset from which centroids are to be chosen.
  - `int k`: The number of clusters to form.
- **Returns:** A vector of `Point` objects representing the initial centroids.

### `assignPointsToCentroids`

- **Purpose:** Assigns each point in the dataset to the nearest centroid.
- **Parameters:**
  - `std::vector<Point>& _points`: The dataset to be clustered.
  - `std::vector<Point>& _centroids`: The current centroids.
- **Returns:** The number of points that changed their cluster assignment in this iteration.

### `recalculateCentroids`

- **Purpose:** Recalculates the position of each centroid based on the current assignments of points to clusters.
- **Parameters:**
  - `std::vector<Point>& _points`: The dataset, with each point assigned to a cluster.
  - `std::vector<Point>& _centroids`: The centroids to be updated.

## Algorithm Steps

1. **Initialization:** Select `k` points as the initial centroids using `initialize_random_centroids`.
2. **Assignment:** Assign each point to the nearest centroid using `assignPointsToCentroids`.
3. **Update:** Recalculate the centroids based on the current cluster assignments using `recalculateCentroids`.
4. **Repeat:** Steps 2 and 3 are repeated until the centroids no longer change significantly or a predetermined number of iterations is reached.

## Convergence

The algorithm is said to have converged when the assignments no longer change. However, it's important to note that K-Means may converge to a local minimum, and the result may depend on the initial choice of centroids. Therefore, it's common practice to run the algorithm multiple times with different initializations and choose the best outcome based on a criterion, such as the sum of squared distances between points and their respective centroids.

## Complexity

The computational complexity of K-Means is generally linear with respect to the number of objects, the number of clusters, and the number of dimensions, making it relatively scalable to large datasets. However, the need to potentially run multiple iterations to avoid local minima can increase the computational cost.
