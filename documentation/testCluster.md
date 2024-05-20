# TestCluster Documentation

## Overview

The `TestCluster.hpp` file contains a suite of tests for the `Cluster` class. These tests ensure that the `Cluster` class constructors and methods behave as expected. The tests cover various constructors, sorting functionality, and other essential methods of the `Cluster` class.

## Class Definition

### Header File: `TestCluster.hpp`

```cpp
#pragma once
#include "../data_processing/Clusters.hpp"
#include <cassert>
#include <vector>
#include <iostream>

class TestClusterConstructor {
public:
    static void runTests() {
        std::cout << "\nRunning Cluster constructor tests..." << std::endl;
        testDefaultConstructor();
        testClusterIdConstructor();
        testClusterIdCenterConstructor();
        testClusterIdPointsConstructor();
        testClusterIdCenterPointsConstructor();
        testClusterIdCenterPointsNumPointsConstructor();
        std::cout << "All Cluster constructor tests passed.\n" << std::endl;
    }

private:
    static void testDefaultConstructor();
    static void testClusterIdConstructor();
    static void testClusterIdCenterConstructor();
    static void testClusterIdPointsConstructor();
    static void testClusterIdCenterPointsConstructor();
    static void testClusterIdCenterPointsNumPointsConstructor();
};

class TestClusterSort {
public:
    static void runTests() {
        std::cout << "\nRunning Cluster sort tests..." << std::endl;
        testSort2D();
        testSort3D();
        testSort4D();
        std::cout << "All Cluster sort tests passed.\n" << std::endl;
    }

private:
    static void testSort2D();
    static void testSort3D();
    static void testSort4D();
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
- `num_points`: An integer representing the number of points in the cluster.

### TestClusterConstructor Class

The `TestClusterConstructor` class contains static methods to test various constructors of the `Cluster` class. Each test method creates a `Cluster` object using a specific constructor and asserts the expected behavior.

### TestClusterSort Class

The `TestClusterSort` class contains static methods to test the sorting functionality of the `Cluster` class. Each test method creates a `Cluster` object, calls the `sort` method, and asserts the expected behavior.

## Expected Output

The tests in the `TestClusterConstructor` and `TestClusterSort` classes do not return any values. Instead, they use assertions to verify the correctness of the `Cluster` class constructors and methods. If all assertions pass, the tests print messages indicating that the tests have passed.

## Algorithm Idea

### Steps

1. **Initialization**: Each test method initializes a `Cluster` object using a specific constructor or method.
2. **Assertions**: The test methods use assertions to verify that the `Cluster` object is correctly initialized or behaves as expected.

### Detailed Algorithm

- **testDefaultConstructor**: Tests the default constructor of the `Cluster` class.
- **testClusterIdConstructor**: Tests the constructor that initializes a `Cluster` object with a cluster ID.
- **testClusterIdCenterConstructor**: Tests the constructor that initializes a `Cluster` object with a cluster ID and center point.
- **testClusterIdPointsConstructor**: Tests the constructor that initializes a `Cluster` object with a cluster ID and a set of points.
- **testClusterIdCenterPointsConstructor**: Tests the constructor that initializes a `Cluster` object with a cluster ID, center point, and a set of points.
- **testClusterIdCenterPointsNumPointsConstructor**: Tests the constructor that initializes a `Cluster` object with a cluster ID, center point, a set of points, and the number of points.
- **testSort2D**: Tests the `sort` method in a 2-dimensional space.
- **testSort3D**: Tests the `sort` method in a 3-dimensional space.
- **testSort4D**: Tests the `sort` method in a 4-dimensional space.

## Advantages of This Implementation

1. **Comprehensive Coverage**: The tests cover a wide range of scenarios, including different constructors and sorting functionality.
2. **Robustness**: The use of assertions ensures that any deviation from the expected behavior is immediately detected, making the `Cluster` class more robust.
3. **Ease of Use**: The `runTests` methods 