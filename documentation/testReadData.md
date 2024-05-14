# Documentation for TestReadData.hpp

The `TestReadData.hpp` file is part of a testing suite designed to ensure the integrity and functionality of the data reading mechanisms within a clustering project. This documentation outlines the purpose, methodology, test inputs, and expected outputs for the tests contained within `TestReadData.hpp`.

## Overview

`TestReadData` is a class that encapsulates a series of unit tests aimed at validating the functionality of the `read_data` function. This function is responsible for reading data points from various file formats (CSV, TXT, NPY) and ensuring that the data is correctly parsed into a vector of `Point` objects. Each test case focuses on a different file format, verifying that the `read_data` function can handle each format correctly.

## Test Methods

### `testReadFromCSV()`

**Purpose:** Validates that the `read_data` function can correctly read and parse points from a CSV file.

**Test Input:** A CSV file located at `"samples/sample_data.csv"` containing 10 points, each with 3 dimensions.

**Expected Output:** A vector of `Point` objects with sizes matching the input file. Each `Point` object should have coordinates corresponding to the data in the CSV file, ensuring that the data is read correctly.

### `testReadFromTXT()`

**Purpose:** Checks the ability of the `read_data` function to read and parse points from a plain text file.

**Test Input:** A TXT file located at `"samples/sample_data.txt"` containing 10 points, each with 3 dimensions.

**Expected Output:** A vector of `Point` objects that accurately reflect the data in the TXT file. The test verifies that each `Point` has the correct coordinates and that the total number of points matches the input file.

### `testReadFromNPY()`

**Purpose:** Ensures that the `read_data` function can correctly read and parse points from an NPY file, a binary file format used by NumPy.

**Test Input:** An NPY file located at `"samples/sample_data.npy"` containing 10 points, each with 3 dimensions.

**Expected Output:** A vector of `Point` objects with coordinates and sizes that match the data stored in the NPY file. This test confirms the ability of `read_data` to handle binary data formats.

### `testCompareAllFormats()`

**Purpose:** Compares the output of `read_data` across all supported file formats to ensure consistency in data parsing.

**Test Input:** Three files located at `"samples/sample_data.csv"`, `"samples/sample_data.txt"`, and `"samples/sample_data.npy"`, each containing the same 10 points with 3 dimensions.

**Expected Output:** The test asserts that the vectors of `Point` objects created from each file format are identical, ensuring that `read_data` provides consistent results regardless of the input file format.

## Utility Methods

### `CreateSampleData()`

**Purpose:** Generates a vector of `Point` objects that serve as expected results for comparison in test cases.

**Output:** A vector of 10 `Point` objects, each with incrementally increasing coordinates from `{1.0, 2.0, 3.0}` to `{28.0, 29.0, 30.0}`, and with `cluster_id` and `distance` properties set for testing purposes.

## Running the Tests

To execute the tests, the `runTests` method is called. This method sequentially invokes each test case and outputs the results to the console, indicating whether each test has passed or failed. Successful completion of all tests without assertion failures confirms the reliability of the `read_data` function across different file formats.