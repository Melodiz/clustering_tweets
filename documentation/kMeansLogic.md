# Documentation for KMeansLogic.hpp

The `KMeansLogic.hpp` header file encapsulates the core logic for the KMeans clustering algorithm. It defines functions essential for initializing centroids, assigning points to the nearest centroids, and recalculating centroids based on the current cluster assignments. This documentation outlines the purpose, parameters, and expected outputs of these functions.

## Functions Overview

### `initialize_random_centroids`

- **Purpose**: Initializes a set of `k` centroids randomly selected from the given dataset.
- **Parameters**:
  - `const std::vector<Point>& points`: The dataset from which centroids are to be chosen.
  - `int k`: The number of centroids (clusters) to initialize.
- **Returns**: `std::vector<Point>` representing the initialized centroids.
- **Expected Output**: A vector of `Point` objects, each representing an initialized centroid. These centroids are randomly selected from the dataset, ensuring no duplicates.

### `assignPointsToCentroids`

- **Purpose**: Assigns each point in the dataset to the nearest centroid based on Euclidean distance.
- **Parameters**:
  - `std::vector<Point>& _points`: The dataset, where each `Point` will be assigned a `cluster_id` corresponding to the nearest centroid.
  - `const std::vector<Point>& _centroids`: The current set of centroids.
- **Returns**: `int` representing the number of points that changed their cluster assignment in this iteration.
- **Expected Output**: The number of points that have been reassigned to a different cluster. This function also updates each `Point` in `_points` with a new `cluster_id` and `distance` to the nearest centroid.

### `recalculateCentroids`

- **Purpose**: Updates the position of each centroid to the mean position of all points assigned to it.
- **Parameters**:
  - `const std::vector<Point>& _points`: The dataset, with each `Point` already assigned to a centroid.
  - `std::vector<Point>& _centroids`: The current set of centroids to be updated.
- **Returns**: None. This function directly modifies the `_centroids` vector.
- **Expected Output**: Centroids are moved to the average position of all points assigned to their cluster. This step is crucial for the iterative improvement of cluster assignments.

## Example Outputs

- **initialize_random_centroids**: Given a dataset of 100 points and `k=3`, this function might return a vector containing 3 `Point` objects selected randomly from the dataset.
- **assignPointsToCentroids**: After the initial assignment of 100 points to 3 centroids, this function might return `95`, indicating that 95 points were assigned to a centroid different from their previous assignment.
- **recalculateCentroids**: This function does not return a value but would result in the centroids' positions being updated to reflect the mean position of their assigned points. For example, if centroid 1 initially had coordinates (2, 3) and after assignment, the mean coordinates of its assigned points are (4, 5), the centroid's new position would be updated to (4, 5).

These functions work together to implement the KMeans clustering algorithm, iteratively improving the cluster assignments until the algorithm converges (i.e., when the number of points changing clusters between iterations falls to zero or a predefined threshold).