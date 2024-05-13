# Documentation for TestStructPoint.hpp

The `TestStructPoint.hpp` file is a comprehensive test suite designed to validate the functionality and integrity of the `Point` struct, which is a fundamental component of the clustering project. This documentation provides an overview of the test cases implemented within `TestStructPoint.hpp`, detailing the purpose, test inputs, and expected outputs for each test.

## Overview

The `TestStructPoint` class encapsulates a series of unit tests aimed at verifying the correct behavior of the `Point` struct's constructors, methods, and operators. Each test is designed to assert the correctness of a specific aspect of the `Point` struct, ensuring its reliability for use in clustering algorithms.

## Test Methods

### `testDefaultConstructor()`

**Purpose:** Validates that the default constructor initializes a `Point` object with default values.

**Test Input:** None (default construction).

**Expected Output:** A `Point` object with an empty coordinate vector, a distance of `INT_MAX`, and a cluster ID of `-1`.

### `testListConstructor()`

**Purpose:** Checks the list constructor's ability to initialize a `Point` object with a given list of coordinates.

**Test Input:** `Point({1.0, 2.0, 3.0})`.

**Expected Output:** A `Point` object with coordinates `[1.0, 2.0, 3.0]`, a distance of `INT_MAX`, and a cluster ID of `-1`.

### `testVectorConstructor()`

**Purpose:** Ensures the vector constructor correctly initializes a `Point` object with a vector of coordinates.

**Test Input:** A vector of doubles `[4.0, 5.0, 6.0]`.

**Expected Output:** A `Point` object with coordinates matching the input vector, a distance of `INT_MAX`, and a cluster ID of `-1`.

### `testCentroidConstructor()`

**Purpose:** Verifies the constructor that initializes a `Point` as a centroid with specified coordinates and cluster ID.

**Test Input:** Coordinates `[7.0, 8.0, 9.0]` and cluster ID `1`.

**Expected Output:** A `Point` object with the specified coordinates, a distance of `0` (indicating a centroid), and the specified cluster ID.

### `testInitializeListConstructor()`

**Purpose:** Tests the initialization of multiple `Point` objects using an initializer list.

**Test Input:** An initializer list of `Point` objects with various coordinates.

**Expected Output:** A vector of `Point` objects each initialized with the specified coordinates, all having a distance of `INT_MAX` and a cluster ID of `-1`.

### `testMixedConstructor()`

**Purpose:** Assesses the constructor's flexibility in handling mixed initialization scenarios, including specifying coordinates, cluster IDs, and distances.

**Test Input:** A mix of `Point` objects initialized with just coordinates, coordinates with cluster IDs, and coordinates with cluster IDs and distances.

**Expected Output:** A vector of `Point` objects correctly initialized according to the varied input parameters.

### `testCalcNorm()`

**Purpose:** Validates the calculation of the Euclidean norm (magnitude) of a point's coordinates.

**Test Input:** A `Point` object with coordinates `[3, 4]`.

**Expected Output:** The calculated norm should be `5.0`, adhering to the Pythagorean theorem.

### `testEqualityOperator()`

**Purpose:** Ensures the equality operator correctly identifies when two `Point` objects have identical coordinates.

**Test Input:** Two `Point` objects with identical coordinates and one with different coordinates.

**Expected Output:** The operator should return `true` for the pair with identical coordinates and `false` for the pair with differing coordinates.

### `testInequalityOperator()`

**Purpose:** Tests the inequality operator's ability to discern differences between `Point` objects.

**Test Input:** Two `Point` objects with identical coordinates and one with different coordinates.

**Expected Output:** The operator should return `false` for the pair with identical coordinates and `true` for the pair with differing coordinates.

### `testLessThanOperator()`

**Purpose:** Verifies the less-than operator's functionality, which compares `Point` objects based on their distance to the centroid or their norm if unassigned.

**Test Input:** Pairs of `Point` objects, some unassigned to any cluster and others with specified distances to their centroids.

**Expected Output:** The operator should correctly identify the relational order based on the context (norm or distance).

## Running the Tests

To execute the tests, call the `runTests()` method of the `TestPoint` class. This method systematically invokes each test case and outputs the results to the console, indicating whether each test has passed or failed. Successful completion of all tests without assertion failures confirms the reliability of the `Point` struct's implementation.