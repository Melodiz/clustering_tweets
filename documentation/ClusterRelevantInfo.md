# ClusterRelevantInfo Documentation

## Overview

The `ClusterRelevantInfo.hpp` file contains the implementation of the `getNeighbors` function, which is designed to find the nearest neighbors to a given center point within a cluster. This function is essential for various clustering algorithms and data analysis tasks where understanding the local neighborhood of a point is crucial.

## Function Definition

### Header File: `ClusterRelevantInfo.hpp`

```cpp
#pragma once
#include "../../clustering_core/modules/structPoint.hpp"
#include "SortingClusters.hpp"
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <vector>

std::vector<Point> getNeighbors(const Point& center, const std::vector<Point>& points, int k);
```

## Input Data Structure

### Point Class

The `Point` class represents a point in a multi-dimensional space. Each `Point` object contains coordinates that define its position in the space. The `Point` class also provides a method `calcDist` to calculate the Euclidean distance between two points.

### getNeighbors Function

- **center**: A `Point` object representing the center point from which neighbors are to be found.
- **points**: A vector of `Point` objects representing the points within the cluster.
- **k**: An integer representing the number of nearest neighbors to find.

## Expected Output

The `getNeighbors` function returns a vector of `Point` objects representing the `k` nearest neighbors to the center point. The neighbors are selected based on their distance from the center and their maximum distance from each other.

## Algorithm Idea

### Steps

1. **Validation**: The function first checks if the value of `k` is valid. If `k` is less than or equal to 0, an empty vector is returned. If `k` is greater than or equal to the number of points, the original vector of points is returned.
2. **Sorting**: The points are sorted by their distance from the center using the `sortPointsByDistance` function.
3. **Selection**: The function starts by selecting the closest point to the center. It then iteratively selects the next point that has the maximum minimum distance from the already selected neighbors. This ensures that the selected neighbors are not only close to the center but also spread out from each other.

### Detailed Algorithm

- **Initialization**: Create a vector `sortedPoints` and sort it by distance from the center. Initialize an empty vector `neighbors` and add the closest point to the center.
- **Iterative Selection**: While the size of `neighbors` is less than `k`:
  - For each point in `sortedPoints`, calculate the minimum distance to any point in `neighbors`.
  - Select the point with the maximum of these minimum distances as the next neighbor.
  - Add the selected point to `neighbors`.
- **Return**: Return the `neighbors` vector.

## Advantages of This Implementation

1. **Balanced Selection**: The algorithm ensures that the selected neighbors are not only close to the center but also spread out from each other, providing a balanced representation of the local neighborhood.
2. **Efficiency**: The sorting step ensures that the initial selection is efficient, and the iterative selection process is optimized to find the best candidates.
3. **Flexibility**: The function can handle different values of `k` and adapt to various cluster sizes, making it versatile for different clustering tasks.
4. **Modularity**: The function leverages the `Point` class and the `sortPointsByDistance` function, promoting code reuse and modularity.

## Conclusion

The `getNeighbors` function in `ClusterRelevantInfo.hpp` provides a robust and efficient way to find the nearest neighbors to a center point within a cluster. Its balanced selection algorithm and flexibility make it a valuable tool for clustering and data analysis tasks.