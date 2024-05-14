# Documentation for readData.hpp

The `readData.hpp` header file is designed to facilitate the reading of data from various file formats into a standardized format used within the application, specifically focusing on handling points for clustering algorithms. It supports reading from CSV, TXT, and NPY files, accommodating both raw and clustered data.

## Functions Overview

### `read_data(std::string path)`

- **Purpose**: Determines the file type based on its extension and delegates the reading process to the corresponding function.
- **Parameters**:
  - `std::string path`: The path to the data file.
- **Returns**: A `std::vector<Point>` containing the points read from the file.
- **Expected Output**: A vector of `Point` objects, each representing a data point. The function automatically detects the file type and reads the data accordingly.

### `read_from_csv(std::string path)`

- **Purpose**: Reads data from a CSV file. It can handle both raw data and data with cluster assignments (`cluster_id`) and distances.
- **Parameters**:
  - `std::string path`: The path to the CSV file.
- **Returns**: A `std::vector<Point>` containing the points read from the CSV file.
- **Expected Output**: For clustered data, each `Point` object in the returned vector will have its coordinates, `cluster_id`, and `distance` populated. For raw data, only the coordinates will be populated.

### `read_from_txt(std::string path)`

- **Purpose**: Reads data from a TXT file, similar to the CSV reader, handling both raw and clustered data.
- **Parameters**:
  - `std::string path`: The path to the TXT file.
- **Returns**: A `std::vector<Point>` containing the points read from the TXT file.
- **Expected Output**: Similar to `read_from_csv`, the output depends on the data type. Clustered data results in `Point` objects with coordinates, `cluster_id`, and `distance`, while raw data results in `Point` objects with only coordinates.

### `read_from_npy(std::string path)`

- **Purpose**: Reads data from an NPY file, which is typically used for N-dimensional arrays. This function is tailored for reading raw data without cluster assignments.
- **Parameters**:
  - `std::string path`: The path to the NPY file.
- **Returns**: A `std::vector<Point>` containing the points read from the NPY file.
- **Expected Output**: A vector of `Point` objects with their coordinates populated from the NPY file. This function assumes raw data, so no `cluster_id` or `distance` is populated.

## Example Outputs

- **CSV/TXT with Clustered Data**:
  - Input: A CSV/TXT file with lines formatted as `cluster_id,distance,x,y,z,...`
  - Output: A vector of `Point` objects where each object has `cluster_id`, `distance`, and coordinates `[x, y, z, ...]` populated.

- **CSV/TXT with Raw Data**:
  - Input: A CSV/TXT file with lines formatted as `x,y,z,...`
  - Output: A vector of `Point` objects with coordinates `[x, y, z, ...]` populated. `cluster_id` and `distance` are not applicable.

- **NPY File**:
  - Input: An NPY file containing an N-dimensional array.
  - Output: A vector of `Point` objects with coordinates populated from the array. Each `Point` corresponds to a row in the NPY array.

This documentation outlines the functionality provided by `readData.hpp` for reading and processing data from various file types into a uniform format suitable for clustering algorithms.