# Documentation for TestKmeansLogic.hpp

The `TestKmeansLogic.hpp` file is designed to validate the functionality and correctness of the KMeans logic implemented in the clustering algorithm. This documentation outlines the purpose, methodology, test inputs, and expected outputs for the tests contained within `TestKmeansLogic.hpp`.

## Overview

The KMeans logic encompasses several critical functions that drive the clustering process, including initializing random centroids, assigning points to the nearest centroids, recalculating centroid positions based on current cluster assignments, and more. The tests in `TestKmeansLogic.hpp` ensure that each of these functions performs as expected under various conditions.

## Test Methods

### `testInitializeRandomCentroids()`

**Purpose:** Verifies that the function `initialize_random_centroids` correctly selects a specified number of unique centroids from the given input points.

**Test Input:** A vector of 10 predefined points in a 2D space.

**Expected Output:** A set of 3 unique centroids chosen from the input points. Each centroid should have a `cluster_id` corresponding to its index in the returned vector and a `distance` value of 0.0.

### `testAssignPointsToCentroids()`

**Purpose:** Ensures that points are correctly assigned to the nearest centroid based on Euclidean distance.

**Test Input:** A set of points and two predefined centroids in a 2D space.

**Expected Output:** Each point is assigned a `cluster_id` that corresponds to the nearest centroid. The function returns the number of points that changed their cluster assignment compared to their initial state.

### `testRecalculateCentroids()`

**Purpose:** Checks that centroids are correctly recalculated as the mean of all points assigned to their cluster.

**Test Input:** A set of points with predefined cluster assignments in both 2D and 3D spaces.

**Expected Output:** For each cluster, the new centroid coordinates are the average of the coordinates of all points assigned to that cluster. The function updates the centroids in place.

## Example Test Case: `testAssignPointsToCentroids()`

### Input

- Points: `[(0.0, 0.0), (10.0, 10.0), (2.0, 2.0), (9.0, 9.0)]`
- Centroids: `[(1.0, 1.0), (8.0, 8.0)]`

### Expected Output

- Points after assignment: `[(0.0, 0.0, cluster_id=0), (10.0, 10.0, cluster_id=1), (2.0, 2.0, cluster_id=0), (9.0, 9.0, cluster_id=1)]`
- Number of changes: `4` (assuming initial `cluster_id` for all points was `-1` or any other number different from the final assignments)

### Verification Steps

1. **Cluster Assignment:** Verify that each point's `cluster_id` matches the expected assignment based on the nearest centroid.
2. **No Coordinate Change:** Ensure that the coordinates of each point remain unchanged after the assignment.
3. **Changes Count:** Confirm that the returned number of changes matches the expected value.

## Conclusion

The tests in `TestKmeansLogic.hpp` are crucial for ensuring the reliability and accuracy of the KMeans clustering implementation. By rigorously testing each component of the KMeans logic, developers can identify and rectify potential issues, thereby enhancing the overall robustness of the clustering algorithm.