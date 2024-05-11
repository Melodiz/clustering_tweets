# `writeData.h` Module Documentation

## Overview

The `writeData.h` module is designed to facilitate the saving of clustering results, including both individual points and centroids, to various file formats. It supports CSV, NPY, and TXT formats, providing flexibility in how data is exported for further analysis or visualization.

## Functions

### `save_result`

- **Description:** Determines the file format based on the file extension and delegates the saving of clustering results to the appropriate function. Parameters taken from KMeans(ND) Class
- **Parameters:**
  - `const std::string& _resultPath`: The path to the output file.
  - `const std::vector<Point>& _points`: A vector of `Point` objects representing the clustered points.
  - `const std::vector<Point>& _centroids`: A vector of `Point` objects representing the centroids of the clusters.
  - `bool _with_coordinates`: A boolean flag indicating whether to include the coordinates of each point in the output. Defaults to `false`.
- **Supported Formats:** CSV, NPY, TXT.

### `save_centroids`

- **Description:** Determines the file format based on the file extension and delegates the saving of centroids to the appropriate function. Parameters taken from KMeans(ND) Class
- **Parameters:**
  - `std::string _resultPath`: The path to the output file.
  - `const std::vector<Point>& _centroids`: A vector of `Point` objects representing the centroids.
- **Supported Formats:** CSV, NPY, TXT.

### `save_result_to_csv`

- **Description:** Saves clustering results to a CSV file. It can optionally include the coordinates of each point.
- **Parameters:**
  - `const std::string& _resultPath`: The path to the output CSV file.
  - `const std::vector<Point>& _points`: A vector of `Point` objects representing the clustered points.
  - `const std::vector<Point>& _centroids`: A vector of `Point` objects representing the centroids of the clusters.
  - `bool _with_coordinates`: A boolean flag indicating whether to include the coordinates of each point in the output. Defaults to `false`.

### `save_centroids_to_csv`

- **Description:** Saves centroids to a CSV file, including their coordinates.
- **Parameters:**
  - `const std::string& _resultPath`: The path to the output CSV file.
  - `const std::vector<Point>& _centroids`: A vector of `Point` objects representing the centroids.

### `save_result_to_txt`

- **Description:** Saves clustering results to a TXT file. It can optionally include the coordinates of each point.
- **Parameters:**
  - `const std::string& _resultPath`: The path to the output TXT file.
  - `const std::vector<Point>& _points`: A vector of `Point` objects representing the clustered points.
  - `const std::vector<Point>& _centroids`: A vector of `Point` objects representing the centroids of the clusters.
  - `bool _with_coordinates`: A boolean flag indicating whether to include the coordinates of each point in the output. Defaults to `false`.

### `save_centroids_to_txt`

- **Description:** Saves centroids to a TXT file, including their coordinates.
- **Parameters:**
  - `const std::string& _resultPath`: The path to the output TXT file.
  - `const std::vector<Point>& _centroids`: A vector of `Point` objects representing the centroids.

### `save_result_to_npy`

- **Description:** Saves clustering results to an NPY file. This function is designed to handle data with coordinates.
- **Parameters:**
  - `const std::string& _resultPath`: The path to the output NPY file.
  - `const std::vector<Point>& _points`: A vector of `Point` objects representing the clustered points.
  - `const std::vector<Point>& _centroids`: A vector of `Point` objects representing the centroids of the clusters.
  - `bool _with_coordinates`: A boolean flag indicating whether to include the coordinates of each point in the output. This parameter is considered in the context of the function but is particularly relevant for NPY format due to its nature of handling numerical data arrays.

## Additional Notes

- The module relies on the `npy.hpp` library for NPY file operations, which provides an interface for reading and writing Numpy-compatible files in C++.
- The `structPoint.h` header is required for the definition of the `Point` structure, which encapsulates the data for individual points and centroids, including their cluster assignments, distances, and coordinates.
- Error handling is implemented for file operations, with the program exiting upon failure to open the specified output file path.
