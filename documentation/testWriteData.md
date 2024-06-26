# Documentation for TestWriteData.hpp

The `TestWriteData.hpp` file is part of the testing framework for the clustering project. It focuses on verifying the functionality of writing clustering results to various file formats, specifically CSV and TXT files. This documentation outlines the purpose, methods, and expected outcomes of the tests contained within `TestWriteData.hpp`.

## Overview

`TestWriteData` is a class dedicated to testing the `save_result` function, which is responsible for writing the clustering results, including data points and their corresponding centroids, to a file. The tests ensure that the output files are correctly formatted and contain the expected data.

## Methods

### `static void runTests()`

This method orchestrates the execution of all tests within the `TestWriteData` class. It calls individual test methods and outputs the status of the tests to the console.

#### Test Flow:
1. `testWriteToCSV()`
2. `testWriteToTXT()`

Upon completion, it reports that all tests have passed if no assertions fail.

### `static void testWriteToCSV()`

Tests the ability of the `save_result` function to correctly write clustering results to a CSV file.

#### Test Input:
- A predefined set of sample data points and centroids.

#### Expected Output:
- A CSV file named `sample_data.csv` in the `output` directory, formatted with data points and centroids. Each row represents a data point, including its cluster ID, distance to the centroid, and coordinates.

### `static void testWriteToTXT()`

Tests the `save_result` function's ability to write clustering results to a TXT file.

#### Test Input:
- The same predefined set of sample data points and centroids used in the CSV test.

#### Expected Output:
- A TXT file named `sample_data.txt` in the `output` directory, containing data points and centroids in a similar format to the CSV test.

## Test Data Creation

The `CreateSampleData` method generates a vector of `Point` objects to be used as test data. Each `Point` object includes coordinates, a cluster ID, and a distance (simulating the distance to the centroid).

### Sample Data Structure:
- Coordinates: Sequential integers simulating a 3D space (e.g., `{1, 2, 3}`).
- Cluster ID: An integer assigned sequentially to each point.
- Distance: A decimal value, increasing by 0.1 for each point, simulating the distance to the centroid.

## Verification Process

After writing the results to files, the test methods read the contents of the output files and compare them to the expected results. The comparison checks if the size of the result matches and if each `Point` object in the output file matches the corresponding `Point` object in the expected results.

## Expected Console Output

Upon successful completion of the tests, the console output will indicate the passing of each test:

```
Running TestWriteData tests...
Test passed: Write to CSV.
Test passed: Write to TXT.
All TestWriteData tests passed.
```

If an assertion fails, the test execution will stop, and an error indicating the failed assertion will be displayed.

## Conclusion

The `TestWriteData.hpp` file provides a robust framework for ensuring the accuracy and reliability of the `save_result` function's ability to write clustering results to different file formats. Through predefined inputs and expected outputs, it verifies the correctness of the output files generated by the clustering process.