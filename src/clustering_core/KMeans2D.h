#include "include/npy.hpp"// https://github.com/llohse/libnpy
#include <algorithm>      // for sorting
#include <chrono>         // for time measurement
#include <cmath>          // for pow and other math functions
#include <fstream>
#include <iostream>
#include <map>
#include <random>// for randomly initializing centroids
#include <string>
#include <utility>
#include <vector>

/**
 * Represents a point in 2D space with additional clustering information.
 */
struct Point {
    double x;       ///< X-coordinate of the point.
    double y;       ///< Y-coordinate of the point.
    double distance;///< Distance from the point to its assigned centroid.
    int cluster_id; ///< ID of the cluster this point is assigned to.

    /**
     * Constructor for creating a point with coordinates, defaulting distance to max double value and cluster ID to -1.
     * @param x X-coordinate of the point.
     * @param y Y-coordinate of the point.
     */
    Point(double x, double y) : x(x), y(y), distance(__DBL_MAX__), cluster_id(-1){};

    /**
     * Constructor for creating a point with full information.
     * @param x X-coordinate of the point.
     * @param y Y-coordinate of the point.
     * @param distance Distance from the point to its assigned centroid.
     * @param cluster_id ID of the cluster this point is assigned to.
     */
    Point(double x, double y, double distance, int cluster_id) : x(x), y(y), distance(distance), cluster_id(cluster_id){};

    /**
     * Constructor for creating a centroid point with specified cluster ID.
     * @param x X-coordinate of the centroid.
     * @param y Y-coordinate of the centroid.
     * @param cluster_id ID of the cluster this centroid represents.
     */
    Point(double x, double y, int cluster_id) : x(x), y(y), distance(0.0), cluster_id(cluster_id){};

    /**
     * Default constructor initializing point to origin with no cluster assignment.
     */
    Point() : x(0.0), y(0.0), distance(0.0), cluster_id(-1){};

    /**
     * Calculates the Euclidean distance between this point and another point.
     * @param other The other point to calculate the distance to.
     * @return The Euclidean distance between this point and the other point.
     */
    double calcDist(const Point& other) const
    {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

// Forward declarations for functions to be implemented elsewhere.
std::vector<Point> read_data(std::string path);
std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k);

/**
 * Implements the K-Means clustering algorithm.
 */
class KMeans
{
protected:
    int _k;       ///< Number of clusters.
    int _max_iter;///< Maximum number of iterations to perform.

    std::vector<Point> _centroids;///< Current centroids of the clusters.

    std::string _pointsPath;   ///< Path to the input file containing points.
    std::string _centroidsPath;///< Path to the output file for centroids.
    std::string _resultPath;   ///< Path to the output file for clustering results.

    std::vector<Point> _points;///< Points to be clustered.

public:
    /**
     * Constructor for KMeans algorithm with file paths for input and output.
     * @param k Number of clusters.
     * @param max_iter Maximum number of iterations.
     * @param pointsPath Path to the file containing points.
     * @param centroidsPath Path to the file where centroids will be saved.
     * @param resultPath Path to the file where results will be saved.
     */
    KMeans(int k, int max_iter, std::string pointsPath, std::string centroidsPath, std::string resultPath);

    /**
     * Constructor for KMeans algorithm with a vector of points.
     * @param k Number of clusters.
     * @param max_iter Maximum number of iterations.
     * @param points Vector of points to be clustered.
     */
    KMeans(int k, int max_iter, std::vector<Point> points);

    /**
     * Default constructor.
     * @param k Number of clusters.
     * @param max_iter Maximum number of iterations.
     */
    KMeans(int k, int max_iter);

    void kMeansClustering();                  ///< Performs the K-Means clustering algorithm.
    int assignPointsToClasters();             ///< Assigns points to the nearest cluster.
    void recalculateCentroids();              ///< Recalculates centroids based on current cluster assignments.
    void save_result_to_csv();                ///< Saves the clustering results to a CSV file.
    void save_centroids_to_csv();             ///< Saves the centroids to a CSV file.
    void run();                               ///< Runs the K-Means algorithm and saves the results and centroids.
    void setPoints(std::vector<Point> points);///< Sets the points to be clustered.
    std::vector<Point> getPoints();           ///< Returns the points involved in clustering.
};

/**
 * Executes the K-Means clustering algorithm, saves the clustering results, and centroids to CSV files.
 */
void KMeans::run()
{
    kMeansClustering();
    save_result_to_csv();
    save_centroids_to_csv();
}

/**
 * Sets the points to be clustered and initializes random centroids.
 * @param points A vector of Point objects to be clustered.
 */
void KMeans::setPoints(std::vector<Point> points)
{
    _points = points;
    _centroids = initialize_random_centroids(_points, _k);
}



/**
 * Executes the K-Means clustering algorithm.
 * 
 * This method iteratively assigns points to the nearest centroid, recalculates the centroids based on the current
 * cluster assignments, and repeats this process until either the points' cluster assignments stop changing or the
 * maximum number of iterations is reached. The method ensures that the algorithm progresses towards minimizing
 * the variance within each cluster, aiming for a partitioning where points are closer to their own cluster's centroid
 * than to others.
 */
void KMeans::kMeansClustering()
{
    int points_changed = _points.size(); // Initialize the number of points changed to the total number of points, ensuring the loop starts.

    // Continue the clustering process until points stop changing clusters or the maximum number of iterations is reached.
    while (points_changed > 0 && _max_iter > 0)
    {
        // Assign points to the nearest cluster and record the number of points that changed clusters.
        points_changed = assignPointsToClasters();

        // Recalculate the position of each centroid based on the current cluster assignments.
        recalculateCentroids();

        // Decrement the remaining number of iterations.
        _max_iter--;
    }
}


/**
 * Assigns each point in the dataset to the nearest centroid, updating the cluster ID and distance for each point.
 * This function iterates over all points in the dataset, calculates the distance to each centroid, and assigns the point
 * to the cluster represented by the nearest centroid. It also counts and returns the number of points that changed their
 * cluster assignment in this iteration, which is useful for determining when the algorithm has converged.
 * 
 * @return The number of points that changed their cluster assignment in this iteration.
 */
int KMeans::assignPointsToClasters()
{
    int points_changed = 0; // Counter for the number of points that change their cluster assignment

    // Iterate over all points in the dataset
    for (int i = 0; i < _points.size(); i++)
    {
        double min_dist = __DBL_MAX__; // Initialize minimum distance to the maximum possible double value
        int min_index = -1; // Initialize the index of the nearest centroid to -1 (indicating no centroid is found yet)

        // Iterate over all centroids to find the nearest one to the current point
        for (int j = 0; j < _centroids.size(); j++)
        {
            double dist = _points[i].calcDist(_centroids[j]); // Calculate the distance from the current point to the current centroid
            if (dist < min_dist) // If this distance is the smallest found so far
            {
                min_dist = dist; // Update the minimum distance
                min_index = j; // Update the index of the nearest centroid
            }
        }

        // If the nearest centroid is different from the current assignment of the point
        if (_points[i].cluster_id != min_index)
        {
            _points[i].cluster_id = min_index; // Update the cluster ID of the point
            _points[i].distance = min_dist; // Update the distance from the point to the nearest centroid
            points_changed++; // Increment the counter for changed points
        }
    }

    return points_changed; // Return the number of points that changed their cluster assignment
}

/**
 * Recalculates the centroids of clusters based on the current assignments of points.
 * 
 * This method first resets the coordinates of each centroid to zero. Then, it iterates through all points,
 * summing their coordinates and counting the number of points per cluster. After accumulating these values,
 * it divides the total coordinates by the number of points in each cluster to find the new centroid positions.
 * Finally, it checks to ensure that all centroids are distinct. If any two centroids are found to be identical,
 * the program will terminate with an error message, as this indicates a potential issue in the clustering process.
 */
void KMeans::recalculateCentroids()
{
    // Reset centroids to origin before recalculating their positions.
    for (int i = 0; i < _centroids.size(); i++)
    {
        _centroids[i].x = 0.0;
        _centroids[i].y = 0.0;
    }

    std::map<int, int> points_per_cluster; // Map to store the count of points in each cluster.

    // Accumulate the coordinates of points in each cluster and count the points per cluster.
    for (int i = 0; i < _points.size(); i++)
    {
        points_per_cluster[_points[i].cluster_id]++;
        _centroids[_points[i].cluster_id].x += _points[i].x; // Update x coordinate of the centroid.
        _centroids[_points[i].cluster_id].y += _points[i].y; // Update y coordinate of the centroid.
    }

    // Recalculate the position of each centroid by averaging the coordinates of points in its cluster.
    for (int i = 0; i < _centroids.size(); i++)
    {
        _centroids[i].x /= points_per_cluster[i];
        _centroids[i].y /= points_per_cluster[i];
    }

    // Ensure all centroids are distinct to prevent clustering anomalies.
    for (int i = 0; i < _centroids.size(); i++)
    {
        for (int j = i + 1; j < _centroids.size(); j++)
        {
            if (_centroids[i].x == _centroids[j].x && _centroids[i].y == _centroids[j].y)
            {
                std::cout << "Centroids are the same" << std::endl;
                exit(1); // Terminate the program if any two centroids are identical.
            }
        }
    }
}

/**
 * Initializes a specified number of random centroids from a given set of points.
 * This function selects `k` distinct points from the input vector to serve as initial centroids for the K-Means algorithm.
 * It ensures that each selected centroid is unique by checking against previously selected indices.
 * 
 * @param points A vector of Point objects from which the centroids are to be chosen.
 * @param k The number of centroids (clusters) to initialize, which should be less than or equal to the size of `points`.
 * @return A vector of Point objects representing the initialized centroids.
 */
std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k)
{
    std::vector<Point> centroids; // Vector to store the selected centroids.
    std::random_device rd; // Non-deterministic random number generator.
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random generator of 32-bit numbers.
    std::uniform_int_distribution<> dis(0, points.size() - 1); // Uniform distribution over the range of point indices.
    std::map<int, bool> used; // Map to track which indices have already been used for centroids.

    for (int i = 0; i < k; i++)
    {
        int index = dis(gen); // Generate a random index.
        while (used.find(index) != used.end()) // Ensure the index has not been used already.
        {
            index = dis(gen); // Generate a new index if the previous one was already used.
        }
        used[index] = true; // Mark the index as used.
        centroids.push_back(points[index]); // Add the point at the selected index to the centroids vector.
    }
    return centroids; // Return the vector of initialized centroids.
}


// READING AND WRITING DATA MODULE
/**
 * Reads data from a specified file and returns a vector of Point objects.
 * This function supports reading from CSV, NPY, and TXT files. It reads the file specified by the path,
 * parses the data into Point objects, and returns a vector containing these points. The function
 * automatically determines the file type by its extension and applies the appropriate parsing method.
 * For CSV and TXT files, it expects the data to be in "x,y" format, with optional headers for CSV files.
 * For NPY files, it uses the libnpy library to read the data, assuming a 2D array where each row represents a point.
 * 
 * @param path The path to the file from which to read the data. The file extension determines the parsing method.
 * @return A vector of Point objects containing the points read from the file.
 * @throws std::runtime_error If the file cannot be opened or the file type is not supported.
 */
std::vector<Point> read_data(std::string path)
{
    // read data from csv file
    if (path.substr(path.size() - 4) == ".csv")
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cout << "File not found" << std::endl;
            exit(1);
        }
        std::vector<Point> points = {};
        std::cout << "Reading..." << path << std::endl;
        std::string line;
        std::getline(file, line);// skip the header line
        while (std::getline(file, line))
        {
            double x = std::stod(line.substr(0, line.find(",")));
            double y = std::stod(line.substr(line.find(",") + 1));
            points.push_back(Point(x, y));
        }
        file.close();
        return points;
    }
    // read data from npy file
    else if (path.substr(path.size() - 4) == ".npy")
    {
        npy::npy_data file = npy::read_npy<double>(path);
        std::cout << "Reading..." << path << std::endl;

        std::vector<Point> points;
        for (int i = 0; i < file.shape[0]; i++)
        {
            double x = file.data[i * file.shape[1]];
            double y = file.data[i * file.shape[1] + 1];
            points.push_back(Point(x, y));
        }
        std::cout << "Read " << points.size() << " points" << std::endl;
        return points;
    }

    // read data from txt file
    else if (path.substr(path.size() - 4) == ".txt")
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cout << "File not found" << std::endl;
            exit(1);
        }
        std::vector<Point> points = {};
        std::cout << "Reading..." << path << std::endl;
        std::string line;
        while (std::getline(file, line))
        {
            double x = std::stod(line.substr(0, line.find(",")));
            double y = std::stod(line.substr(line.find(",") + 1));
            points.push_back(Point(x, y));
        }
        file.close();
        return points;
    }
    // not supported file type
    else
    {
        std::cout << "File type not supported" << std::endl;
        std::cout << "Supported file types: csv, npy, txt" << std::endl;
        exit(1);
    }
}

/**
 * Saves the clustering results to a CSV file.
 * 
 * This method writes the clustering results to a CSV file specified by `_resultPath`. Each line in the file
 * represents a point, detailing its cluster assignment, distance from the centroid, and coordinates (x, y).
 * The file begins with a header row specifying the format of the data: "cluster,distance,x,y".
 * 
 * If the file cannot be opened for writing, an error message is displayed and the function returns early.
 * Upon successful writing, a confirmation message is displayed indicating the file path where the results were saved.
 */
void KMeans::save_result_to_csv()
{
    std::cout << "Saving..." << std::endl;
    std::ofstream file(_resultPath); // Attempt to open the file for writing.
    if (!file.is_open()) // Check if the file was successfully opened.
    {
        std::cout << "Error saving the file" << std::endl;
        return; // Exit the function if the file could not be opened.
    }
    file << "cluster,distance,x,y" << "\n"; // Write the header row to the file.

    for (int i = 0; i < _points.size(); i++) // Iterate over each point in the clustering result.
    {
        // Create a string representing the point's data.
        std::string line = std::to_string(_points[i].cluster_id) +
                           ',' + std::to_string(_points[i].distance) + ',' +
                           std::to_string(_points[i].x) + ',' + std::to_string(_points[i].y) + "\n";

        file << line; // Write the point's data to the file.
    }
    std::cout << "Saved to: " << _resultPath << std::endl; // Confirm successful save.
    file.close(); // Close the file.
}

/**
 * Saves the centroids to a CSV file.
 * 
 * This method writes the current centroids to a CSV file specified by `_centroidsPath`.
 * Each line in the file represents a centroid, detailing its cluster index and coordinates (x, y).
 * The file begins with a header row specifying the format of the data: "```cpp
/**
 * Saves the centroids to a CSV file.
 * 
 * This method writes the current centroids to a CSV file specified by `_centroidsPath`. Each line in the file
 * represents a centroid, detailing its cluster index and coordinates (x, y). The file begins with a header row
 * specifying the format of the data: "cluster,x,y".
 * 
 * If the file cannot be opened for writing, an error message is displayed and the function exits early.
 * Upon successful writing, the centroids are saved, and the file is closed.
 */
void KMeans::save_centroids_to_csv()
{
    std::ofstream file(_centroidsPath); // Attempt to open the file for writing.
    if (!file.is_open()) // Check if the file was successfully opened.
    {
        std::cout << "Error saving the centroids" << std::endl;
        return; // Exit the function if the file could not be opened.
    }
    file << "cluster,x,y" << "\n"; // Write the header row to the file.

    for (int i = 0; i < _centroids.size(); i++) // Iterate over each centroid.
    {
        // Write the cluster index and coordinates of the centroid to the file.
        file << i << ',' << _centroids[i].x << ',' << _centroids[i].y << '\n';
    }
    file.close(); // Close the file after writing.
}