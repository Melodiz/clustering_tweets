# Documentation for KMeansND.hpp

The `KMeansND.hpp` file defines the `KMeansND` class, which implements the K-Means clustering algorithm for N-dimensional data. This class provides methods for initializing the clustering process, executing the algorithm, and saving the results.

## Class Overview

### Constructors

- **`KMeansND(int k, int max_iter, std::string pointsPath, std::string centroidsPath, std::string resultPath)`**: Initializes the KMeansND object with the number of clusters (`k`), maximum iterations (`max_iter`), and paths for points, centroids, and results. It reads the initial points from the specified path and initializes random centroids.

- **`KMeansND(int k, int max_iter, std::vector<Point> points)`**: Initializes the KMeansND object with `k`, `max_iter`, and a vector of `Point` objects. It uses the provided points to initialize random centroids.

- **`KMeansND(int k, int max_iter)`**: Initializes the KMeansND object with `k` and `max_iter` but without initial points or paths. Points and paths must be set using setter methods before clustering.

### Methods

- **`void Cluster(bool showStatus)`**: Executes the K-Means clustering algorithm. If `showStatus` is true, it prints the status of each iteration.

- **`void save()`**: Saves the clustering results and centroids to the specified paths. The format (CSV, TXT, etc.) and inclusion of coordinates are determined by the object's properties.

- **Setters and Getters**: Methods to set and get properties of the KMeansND object, including the number of clusters (`k`), maximum iterations (`max_iter`), paths for points, centroids, and results, and whether to include coordinates in the output.

### Protected and Public Members

- **`_k`**: The number of clusters.
- **`_max_iter`**: The maximum number of iterations to run the algorithm.
- **`_with_coordinates`**: A flag indicating whether to include point coordinates in the output.
- **`_centroids`**: A vector of `Point` objects representing the centroids.
- **`_pointsPath`, `_centroidsPath`, `_resultPath`**: Paths for input points, output centroids, and output results, respectively.
- **`_points`**: A vector of `Point` objects representing the data points.

## Expected Outputs

### Clustering Process

When the `Cluster` method is called with `showStatus = true`, the console output will show the progress of the clustering process, including the current iteration and the number of points that changed clusters. For example:

```
Iteration 1: 150 points changed clusters.
Iteration 2: 50 points changed clusters.
...
Clustering finished
```

### Saving Results

The `save` method does not produce console output but saves the clustering results and centroids to the specified paths. The format and content depend on the file type and whether coordinates are included. For example, a CSV file saved with coordinates might look like this:

```
cluster_id,distance,x,y,z,...
0,0.123,1.2,2.3,3.4,...
1,0.456,4.5,5.6,6.7,...
...
```

And a centroids file might contain:

```
x,y,z,...
2.1,3.2,4.3,...
5.4,6.5,7.6,...
...
```

## Usage Example

To use the `KMeansND` class, you would typically instantiate it with the desired parameters, call the `Cluster` method to perform clustering, and then call `save` to write the results:

```cpp
KMeansND kmeans(3, 100, "path/to/points.csv", "path/to/centroids.csv", "path/to/results.csv");
kmeans.Cluster(true);
kmeans.save();
```

This example initializes a KMeansND object for 3 clusters and a maximum of 100 iterations, performs clustering on data read from "path/to/points.csv", and saves the results and centroids to the specified paths.