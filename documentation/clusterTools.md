# Documentation for ClusterTools

The `ClusterTools` module provides a set of utility functions designed to assist in the clustering process, particularly with KMeans clustering. These functions facilitate the tracking and debugging of the clustering process by providing insights into the distribution of data points across clusters, the progress of iterations, and a detailed view of the current state of centroids and points.

## Functions

### `returnClustersSize`

- **Description**: This function calculates the size of each cluster by counting the number of points belonging to each cluster.
- **Parameters**: `std::vector<Point> _points` - A vector of `Point` objects, where each `Point` represents a data point in the clustering space and contains a `cluster_id` indicating its current cluster assignment.
- **Returns**: `std::map<int, int>` - A map where the key is the `cluster_id` and the value is the count of points in that cluster.
- **Example Output**:
  ```
  Cluster 0: 150
  Cluster 1: 123
  Cluster 2: 127
  ```
  This output indicates that there are three clusters with IDs 0, 1, and 2, containing 150, 123, and 127 points, respectively.

### `iterationStatus`

- **Description**: Prints the status of the current iteration during the clustering process, including the iteration number and the number of points that changed their cluster assignment in that iteration.
- **Parameters**:
  - `int iteration` - The current iteration number.
  - `int pointsChanged` - The number of points that changed their cluster assignment in the current iteration.
- **Output**: A string indicating the iteration number and the number of points changed, printed to the standard output.
- **Example Output**:
  ```
  Iteration: 5, Points changed: 321
  ```
  This output signifies that in iteration 5, a total of 321 points changed their cluster assignment.

### `debugShowFullData`

- **Description**: Provides a detailed view of the current state of centroids and points, useful for debugging purposes. It prints the coordinates of centroids and points, along with their cluster assignments.
- **Parameters**:
  - `std::vector<Point> _points` - A vector of `Point` objects representing the data points.
  - `std::vector<Point> _centroids` - A vector of `Point` objects representing the centroids of the clusters.
- **Output**: A detailed listing of centroids and points, including their coordinates and cluster assignments, printed to the standard output.
- **Example Output**:
  ```
  -------------------------------------------------------
  Centroids:
  [1.5, 2.5, 3.5] Cluster ID: 0
  [4.5, 5.5, 6.5] Cluster ID: 1
  [7.5, 8.5, 9.5] Cluster ID: 2

  Points:
  [1, 2, 3] Cluster ID: 0
  [4, 5, 6] Cluster ID: 1
  [7, 8, 9] Cluster ID: 2
  ...
  -------------------------------------------------------
  ```
  This output shows the coordinates of each centroid and point, along with their respective cluster IDs. The ellipsis (`...`) indicates that the list of points continues.

## Usage

These functions are primarily used for monitoring and debugging the KMeans clustering process. They help in understanding how data points are distributed across clusters, how the clustering process progresses over iterations, and provide a detailed snapshot of the current state of the clustering, which is invaluable for debugging and optimization purposes.