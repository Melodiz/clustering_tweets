# TestClusterNeighbors Documentation

## Overview

The `TestClusterNeighbors.hpp` file contains a suite of tests for the `getNeighbors` function in the `Cluster` class. These tests ensure that the `getNeighbors` function behaves as expected under various conditions and edge cases. The tests cover different dimensional spaces, disjoint point selection, and extreme cases.

## Class Definition

### Header File: `TestClusterNeighbors.hpp`

```cpp
#pragma once
#include "../data_processing/Clusters.hpp"
#include <cassert>
#include <iostream>
#include <set>

class TestClusterNeighbors {
public:
    static void runTests() {
        std::cout << "\nRunning tests for ClusterNeighbors..." << std::endl;
        testGetNeighbors2D();
        testGetNeighbors3D();
        testGetNeighbors4D();
        testDisjointChoose();
        testExtremeCases();
        std::cout << "All ClusterNeighbors tests passed." << std::endl;
    }

private:
    static void testGetNeighbors2D();
    static void testGetNeighbors3D();
    static void testGetNeighbors4D();
    static void testDisjointChoose();
    static void testExtremeCases();
};
```

## Input Data Structure

### Point Class

The `Point` class represents a point in a multi-dimensional space. Each `Point` object contains coordinates that define its position in the space. The `Point` class also provides a method `calcDist` to calculate the Euclidean distance between two points.

### Cluster Class

The `Cluster` class represents a cluster of points. Each `Cluster` object contains:
- `cluster_id`: An integer representing the cluster ID.
- `center`: A `Point` object representing the center of the cluster.
- `points`: A vector of `Point` objects representing the points within the cluster.

### TestClusterNeighbors Class

The `TestClusterNeighbors` class contains static methods to test the `getNeighbors` function. Each test method creates a `Cluster` object, calls the `getNeighbors` function, and asserts the expected behavior.

## Expected Output

The tests in the `TestClusterNeighbors` class do not return any values. Instead, they use assertions to verify the correctness of the `getNeighbors` function. If all assertions pass, the tests print messages indicating that the tests have passed.

## Algorithm Idea

### Steps

1. **Initialization**: Each test method initializes a `Cluster` object with a center point and a set of points.
2. **Neighbor Selection**: The `getNeighbors` function is called with a specified value of `k` to find the nearest neighbors.
3. **Assertions**: The test methods use assertions to verify that the number of neighbors is correct, the neighbors are correctly selected, and edge cases are handled properly.

### Detailed Algorithm

- **testGetNeighbors2D**: Tests the `getNeighbors` function in a 2-dimensional space.
- **testGetNeighbors3D**: Tests the `getNeighbors` function in a 3-dimensional space.
- **testGetNeighbors4D**: Tests the `getNeighbors` function in a 4-dimensional space.
- **testDisjointChoose**: Tests the selection of disjoint points to ensure that the selected neighbors are not too close to each other.
- **testExtremeCases**: Tests various extreme cases, such as when `k` is larger than the number of points, all points are equidistant from the center, and there are no points in the cluster.

## Advantages of This Implementation

1. **Comprehensive Coverage**: The tests cover a wide range of scenarios, including different dimensional spaces, disjoint point selection, and extreme cases.
2. **Robustness**: The use of assertions ensures that any deviation from the expected behavior is immediately detected, making the `getNeighbors` function more robust.
3. **Ease of Use**: The `runTests` method provides a simple way to run all tests and verify the correctness of the `getNeighbors` function.
4. **Modularity**: The test methods are modular and can be easily extended or modified to include additional test cases.

## Conclusion

The `TestClusterNeighbors.hpp` file provides a comprehensive suite of tests for the `getNeighbors` function in the `Cluster` class. These tests ensure that the function behaves as expected under various conditions and edge cases, making the implementation more robust and reliable.