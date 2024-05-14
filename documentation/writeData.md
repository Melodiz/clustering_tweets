# Documentation for writeData.hpp

The `writeData.hpp` header file provides functionality to save clustering results and centroids to various file formats, including CSV, TXT, and NPY. It supports saving with or without point coordinates, depending on the requirements of the analysis or further processing needs.

## Functions Overview

### Saving Clustering Results

- **`save_result_to_csv`**: Saves clustering results to a CSV file. If `_with_coordinates` is true, it includes the coordinates of each point along with its cluster ID and distance to the nearest centroid.

- **`save_result_to_txt`**: Saves clustering results to a TXT file. Similar to the CSV function, it can include coordinates if `_with_coordinates` is set to true.

- **`save_result_to_npy`**: Saves clustering results to an NPY file, a binary file format for persisting numpy arrays. This function is particularly useful for Python-based data analysis workflows.

### Saving Centroids

- **`save_centroids_to_csv`**: Saves the centroids to a CSV file, including their cluster ID, distance (usually zero as it's a centroid), and coordinates.

- **`save_centroids_to_txt`**: Similar to the CSV function, but saves the centroids to a TXT file.

- **`save_centroids_to_npy`**: Saves the centroids to an NPY file, useful for numpy-based processing.

### General Saving Functions

- **`save_result`**: Determines the file type based on its extension and calls the appropriate function to save clustering results. It supports CSV, TXT, and NPY formats.

- **`save_centroids`**: Similar to `save_result`, but specifically for saving centroids to the chosen file format based on the file extension.

## Expected Outputs

### CSV/TXT Output Format

When saving with coordinates (`_with_coordinates = true`), the output format for both CSV and TXT files will include headers followed by the data rows. For example:

```
cluster_id,distance,x0,x1,x2,...
0,0.0,1.2,2.3,3.4,...
1,0.1,4.5,5.6,6.7,...
...
```

Without coordinates, the output will only include the cluster ID and distance:

```
cluster_id,distance
0,0.0
1,0.1
...
```

### NPY Output

The NPY file is a binary format and will not be human-readable. However, when loaded using numpy in Python, it will represent an array where each row corresponds to a point or centroid, including its cluster ID, distance, and coordinates (if saved with coordinates).

## Usage Example

To save clustering results to a CSV file with coordinates:

```cpp
std::vector<Point> points = {/* Populate with clustering results */};
std::vector<Point> centroids = {/* Populate with centroids */};
std::string resultPath = "clustering_results.csv";
save_result(resultPath, points, centroids, true);
```

This will create a CSV file named `clustering_results.csv` with each point's cluster ID, distance to its centroid, and coordinates.