# Documentation for structPoint.hpp

The `structPoint.hpp` header file defines the `Point` structure, which is a fundamental component in representing both data points and centroids within N-dimensional space for clustering algorithms. This structure encapsulates the coordinates of a point, its distance from the nearest centroid, and the cluster ID to which it belongs.

## Structure Overview

### `Point`

- **Attributes**:
  - `std::vector<double> coords`: Represents the coordinates of the point in N-dimensional space.
  - `double distance`: The Euclidean distance from the nearest centroid. It is initialized to `INT_MAX` for data points to signify that they are initially at an infinite distance from any centroid.
  - `int cluster_id`: The ID of the cluster to which the point is assigned. It is initialized to `-1` to indicate that the point has not been assigned to any cluster.

### Constructors

- **Point(const std::vector<double>& coords, int cluster_id, double distance)**: Initializes a point with specified coordinates, cluster ID, and distance. This constructor is versatile for initializing both data points and centroids with all attributes.
- **Point(std::initializer_list<double> list)**: Allows for easy initialization of a point with a list of coordinates. This constructor sets `distance` to `INT_MAX` and `cluster_id` to `-1`, making it suitable for data points.
- **Point(const std::vector<double>& coords)**: Similar to the initializer list constructor but takes a vector of doubles. It sets `distance` to `INT_MAX` and `cluster_id` to `-1`.
- **Point(const std::vector<double>& coords, int cluster_id)**: Initializes a centroid with specified coordinates and cluster ID. The `distance` is set to `0` as it is not relevant for centroids.
- **Point()**: The default constructor initializes a point with no coordinates, maximum distance, and no cluster assigned.

### Member Functions

- **double calcDist(const Point& other) const**: Calculates the Euclidean distance between this point and another point. This function is essential for clustering algorithms to determine the proximity of points to centroids.
- **double CalcNorm() const**: Calculates the norm (magnitude) of the point, which can be useful for sorting or comparing points based on their distance from the origin.

### Operator Overloads

- **bool operator==(const Point& other) const**: Checks if two points are equal based on their coordinates.
- **bool operator!=(const Point& other) const**: Checks if two points are not equal.
- **bool operator<(const Point& other) const**: Compares two points based on their distance from the nearest centroid or, if unassigned, their norms.
- **friend std::ostream& operator<<(std::ostream& os, const Point& p)**: Overloads the output stream operator to print the details of a point, including its cluster ID, distance, and coordinates.

## Example Outputs

When using the `<<` operator to print a `Point` object, the output format will be as follows:

- For a point with coordinates `[1.0, 2.0, 3.0]`, cluster ID `1`, and distance `5.0`:
  ```
  cluster_id: 1, distance: 5, coords: [ 1 2 3 ]
  ```

- For an unassigned point with coordinates `[4.5, 5.5, 6.5]`:
  ```
  cluster_id: -1, distance: 2147483647, coords: [ 4.5 5.5 6.5 ]
  ```

This documentation provides a comprehensive overview of the `Point` structure defined in `structPoint.hpp`, detailing its purpose, constructors, member functions, and operator overloads, along with examples of expected outputs.