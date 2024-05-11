# Documentation for structPoint.hpp

The `structPoint.hpp` file defines a `Point` structure, which is a fundamental component for representing points in N-dimensional space. This structure is versatile, supporting both data points and centroids within clustering algorithms such as k-means. Below is a detailed explanation of its components and usage.

## Structure Overview

### Attributes

- `coords`: A `std::vector<double>` representing the coordinates of the point in N-dimensional space.
- `distance`: A `double` indicating the distance from the nearest centroid. It is initialized to `INT_MAX` for data points to signify that they are initially at an infinite distance from any centroid.
- `cluster_id`: An `int` representing the ID of the cluster to which the point belongs. It is initialized to `-1` to indicate that the point is not yet assigned to any cluster.

### Constructors

- **Vector Constructor**: Initializes a point with a given vector of coordinates. This is typically used for data points.
- **Centroid Constructor**: Initializes a centroid with specified coordinates and a cluster ID. This is used for centroids in clustering algorithms.
- **Default Constructor**: Initializes a point with no coordinates, maximum distance, and no cluster assigned.
- **Initializer List Constructor**: Allows for easy inline initialization of points with an initializer list.

### Methods

- `calcDist(const Point& other) const`: Calculates the Euclidean distance between this point and another point.

### Destructor

- A default destructor is provided, which is a good practice for structures and classes that may be extended or used polymorphically.

## Sample Usage

### Creating Points

```cpp
// Creating a data point at coordinates (1.0, 2.0, 3.0)
Point dataPoint({1.0, 2.0, 3.0});

// Creating a centroid for cluster 0 at coordinates (4.0, 5.0, 6.0)
Point centroid({4.0, 5.0, 6.0}, 0);
```

### Calculating Distance Between Points

```cpp
double distance = dataPoint.calcDist(centroid);
std::cout << "Distance between dataPoint and centroid: " << distance << std::endl;
```

### Accessing and Modifying Attributes

```cpp
// Accessing the coordinates of a point
std::vector<double> coordinates = dataPoint.coords;

// Modifying the cluster ID of a point
dataPoint.cluster_id = 1; // Assigning to cluster 1

// Checking the distance attribute (should be INT_MAX for unassigned data points)
std::cout << "Initial distance from centroid: " << dataPoint.distance << std::endl;
```

## Conclusion

The `Point` structure in `structPoint.hpp` is designed to be a flexible and intuitive way to represent points in N-dimensional space for clustering algorithms. Its attributes and methods provide all the necessary functionality for managing points, calculating distances, and handling cluster assignments. This makes it an essential component for any project involving spatial data and clustering techniques.
