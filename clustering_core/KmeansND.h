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
 * @struct Point
 * @brief Represents a point in N-dimensional space.
 * 
 * This structure is used to represent both data points and centroids in a clustering algorithm.
 * It contains coordinates in N-dimensional space, the distance from the nearest centroid, and the cluster ID to which the point belongs.
 */
struct Point {
    std::vector<double> coords; ///< Coordinates of the point in N-dimensional space.
    double distance; ///< Distance from the nearest centroid. Initialized to INT_MAX for data points.
    int cluster_id;  ///< ID of the cluster to which the point belongs. Initialized to -1 to indicate no cluster assigned.

    /**
     * @brief Constructor for creating a point from a vector of coordinates.
     * @param coords A vector of doubles representing the coordinates of the point in N-dimensional space.
     * This constructor is typically used for initializing data points.
     */
    Point(const std::vector<double>& coords) : coords(coords), distance(INT_MAX), cluster_id(-1) {};

    /**
     * @brief Constructor for creating a centroid with specified coordinates and cluster ID.
     * @param coords A vector of doubles representing the coordinates of the centroid in N-dimensional space.
     * @param cluster_id An integer representing the unique ID of the cluster.
     * This constructor is used for initializing centroids.
     */
    Point(const std::vector<double>& coords, int cluster_id) : coords(coords), distance(0), cluster_id(cluster_id) {};

    /**
     * @brief Default constructor.
     * Initializes a point with no coordinates, maximum distance, and no cluster assigned.
     */
    Point() : distance(INT_MAX), cluster_id(-1), coords({}) {};

    /**
     * @brief Constructor for creating a point from an initializer list.
     * @param list An initializer list of doubles representing the coordinates of the point.
     * This constructor allows for easy inline initialization of points.
     */
    Point(std::initializer_list<double> list) : coords(list) {}

    /**
     * @brief Calculates the Euclidean distance between this point and another point.
     * @param other A reference to another Point object.
     * @return A double representing the Euclidean distance between the two points.
     */
    double calcDist(const Point& other) const
    {
        double sum = 0;
        for (int i = 0; i < coords.size(); i++)
        {
            sum += pow(coords[i] - other.coords[i], 2);
        }
        return sqrt(sum);
    }

    /**
     * @brief Default destructor.
     */
    ~Point() = default;
};

std::vector<Point> read_data(std::string path);
std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k);
/**
 * @class KMeansND
 * @brief Implements the K-Means clustering algorithm for N-dimensional data.
 *
 * This class encapsulates the functionality required to perform K-Means clustering on a set of N-dimensional points.
 * It supports initializing centroids randomly, assigning points to the nearest centroids, recalculating centroids,
 * and saving the results to a file. The class allows for clustering with or without storing the coordinates of points
 * in the output file to save memory.
 */
class KMeansND
{
protected:
    int _k;       ///< Number of clusters.
    int _max_iter;///< Maximum number of iterations to perform.
    bool _with_coordinates;///< Flag to determine if point coordinates are saved in the output file.

    std::vector<Point> _centroids;///< Vector storing the centroids of the clusters.

    std::string _pointsPath;   ///< Path to the input file containing the points.
    std::string _centroidsPath;///< Path to the output file for saving centroids.
    std::string _resultPath;   ///< Path to the output file for saving clustering results.

    std::vector<Point> _points;///< Vector storing all points to be clustered.

public:
    /**
     * @brief Constructor for initializing KMeansND with file paths.
     * @param k Number of clusters.
     * @param max_iter Maximum number of iterations.
     * @param pointsPath Path to the input file containing the points.
     * @param centroidsPath Path to the output file for saving centroids.
     * @param resultPath Path to the output file for saving clustering results.
     */
    KMeansND(int k, int max_iter, std::string pointsPath, std::string centroidsPath, std::string resultPath);

    /**
     * @brief Constructor for initializing KMeansND with a vector of points.
     * @param k Number of clusters.
     * @param max_iter Maximum number of iterations.
     * @param points Vector of points to be clustered.
     */
    KMeansND(int k, int max_iter, std::vector<Point> points);

    /**
     * @brief Minimal constructor for KMeansND.
     * @param k Number of clusters.
     * @param max_iter Maximum number of iterations.
     */
    KMeansND(int k, int max_iter);

    /**
     * @brief Default destructor.
     */
    ~KMeansND() = default;

    /**
     * @brief Copy constructor.
     * @param other Another instance of KMeansND to be copied.
     */
    KMeansND(const KMeansND& other);

    void kMeansClustering(); ///< Performs the K-Means clustering algorithm.
    int assignPointsToClasters(); ///< Assigns each point to the nearest cluster.
    void recalculateCentroids(); ///< Recalculates the centroids of the clusters.
    void save_result(); ///< Saves the clustering results to a file.
    void save_centroids(); ///< Saves the centroids to a file.
    void run(bool show_time); ///< Runs the K-Means clustering algorithm and saves the results.

    void setPoints(std::vector<Point> points); ///< Sets the points to be clustered.
    std::vector<Point> getPoints(); ///< Returns the points being clustered.
    std::vector<Point> getCentroids(); ///< Returns the centroids of the clusters.
    void setCentroids(std::vector<Point> centroids); ///< Sets the centroids of the clusters.
    void setMaxIter(int max_iter); ///< Sets the maximum number of iterations.
    void setPointsPath(std::string pointsPath); ///< Sets the path to the input file containing the points.
    void setCentroidsPath(std::string centroidsPath); ///< Sets the path to the output file for saving centroids.
    void setResultPath(std::string resultPath); ///< Sets the path to the output file for saving clustering results.
    void setWithCoordinates(bool with_coordinates); ///< Determines if point coordinates are saved in the output file.
    void setK(int k); ///< Sets the number of clusters.
    int getK(); ///< Returns the number of clusters.
    std::map<int, int> getClustersSize(); ///< Returns the size of each cluster.
};
/**
 * @brief Runs the K-Means clustering algorithm and optionally measures execution time.
 * 
 * This method orchestrates the K-Means clustering process by calling the methods to perform clustering,
 * save the results, and save the centroids. If requested, it measures the time taken to complete the clustering
 * process and outputs it to the standard output.
 * 
 * @param show_time If true, the execution time of the clustering process is measured and displayed. Defaults to false.
 */
void KMeansND::run(bool show_time = false)
{
    if (show_time)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now(); // Mark the start time
        kMeansClustering(); // Perform the clustering
        save_result(); // Save the clustering results
        save_centroids(); // Save the centroids
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); // Mark the end time
        // Calculate and display the elapsed time in milliseconds
        std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    }
    else
    {
        kMeansClustering(); // Perform the clustering without timing
        save_result(); // Save the clustering results
        save_centroids(); // Save the centroids
    }
}

/**
 * @brief Sets the points to be clustered and initializes the centroids randomly.
 * 
 * This method assigns a given vector of points to the KMeansND instance for clustering.
 * It also initializes the centroids randomly based on these points and the specified number of clusters (_k).
 * The centroids are chosen randomly from the given points.
 * 
 * @param points A vector of Point objects representing the data points to be clustered.
 */

void KMeansND::setPoints(std::vector<Point> points)
{
    _points = points; // Assign the given points to the instance's points vector.
    _centroids = initialize_random_centroids(_points, _k); // Initialize centroids randomly from the given points.
}

void KMeansND::kMeansClustering()
{
    int points_changed = _points.size();// amount of points changed during clustering iteration
    while (points_changed > 0 && _max_iter > 0)
    {
        // assign points to clusters and save the number of changed points
        points_changed = assignPointsToClasters();
        // recalculate centroids
        recalculateCentroids();
        _max_iter--;
    }
}

int KMeansND::assignPointsToClasters()
{
    int points_changed = 0;
    for (int i = 0; i < _points.size(); i++)
    {
        double min_dist = __DBL_MAX__;
        int min_index = -1;
        for (int j = 0; j < _centroids.size(); j++)
        {
            double dist = _points[i].calcDist(_centroids[j]);
            if (dist < min_dist)
            {
                min_dist = dist;
                min_index = j;
            }
        }
        if (_points[i].cluster_id != min_index)
        {
            _points[i].cluster_id = min_index;
            _points[i].distance = min_dist;
            points_changed++;
        }
    }
    return points_changed;
}

void KMeansND::recalculateCentroids()
{
    // reset centroids
    for (int i = 0; i < _centroids.size(); i++)
    {
        _centroids[i].coords.clear();
        _centroids[i].distance = 0;
    }
    // recalculate centroids

    std::map<int, int> points_per_cluster;  // store the number of points in each cluster
    for (int i = 0; i < _points.size(); i++)// for each point
    {
        points_per_cluster[_points[i].cluster_id]++;// update the number of points in each cluster
        for (int j = 0; j < _points[i].coords.size(); j++)
        {
            // update each coordinate of the centroid
            _centroids[_points[i].cluster_id].coords[j] += _points[i].coords[j];
        }
    }
    // divide each coordinate by the number of points in the cluster
    for (int i = 0; i < _centroids.size(); i++)
    {
        for (int j = 0; j < _centroids[i].coords.size(); j++)
        {
            _centroids[i].coords[j] /= points_per_cluster[i];
        }
    }
    // check that all centroids are different
    for (int i = 0; i < _centroids.size(); i++)
    {
        for (int j = i + 1; j < _centroids.size(); j++)
        {
            bool is_different = false;
            for (int k = 0; k < _centroids[i].coords.size(); k++)
            {
                if (_centroids[i].coords[k] != _centroids[j].coords[k])
                {
                    is_different = true;
                    break;
                }
            }
            if (is_different)
            {
                std::cout << "centroids are the same" << std::endl;
                exit(1);
            }
        }
    }
}

std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k)
{
    // check that the number of centroids is less than the number of points
    if (k > points.size())
    {
        std::cout << "The number of centroids is greater than the number of points" << std::endl;
        std::cout << "Number of centroids: " << k << " Number of points: " << points.size() << std::endl;
        exit(1);
    }
    // initialize centroids
    std::vector<Point> centroids;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, points.size() - 1);
    std::map<int, bool> used;// store used the indexes of centroids
    for (int i = 0; i < k; i++)
    {
        int index = dis(gen);
        while (used[index])
        {
            index = dis(gen);
        }
        used[index] = true;
        centroids.push_back(points[index]);
    }
    // check that centroids initialized correctly

    return centroids;
}

// READING AND WRITING DATA MODULE

std::vector<Point> read_data(std::string path)
{
    // Determine the file type based on its extension
    std::string extension = path.substr(path.size() - 4);

    // Initialize a vector to hold the points
    std::vector<Point> points;

    // Read data from a CSV file
    if (extension == ".csv")
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cout << "File " << path << " not found" << std::endl;
            exit(1);
        }
        std::cout << "Reading..." << path << std::endl;
        std::string line;
        std::getline(file, line);// Skip the header line

        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::vector<double> values;
            std::string value;
            while (std::getline(iss, value, ','))
            {
                values.push_back(std::stod(value));
            }
            points.push_back(Point(values));// Assuming Point constructor can take a vector<double> for N-dimensional points
        }
        file.close();
    }
    // Read data from an NPY file
    else if (extension == ".npy")
    {
        npy::npy_data file = npy::read_npy<double>(path);
        std::cout << "Reading..." << path << std::endl;

        for (int i = 0; i < file.shape[0]; i++)
        {
            std::vector<double> values;
            for (int j = 0; j < file.shape[1]; j++)
            {
                values.push_back(file.data[i * file.shape[1] + j]);
            }
            points.push_back(Point(values));// Assuming Point constructor can take a vector<double> for N-dimensional points
        }
        std::cout << "Read " << points.size() << " points" << std::endl;
    }
    // Read data from a TXT file
    else if (extension == ".txt")
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cout << "File " << path << " not found" << std::endl;
            exit(1);
        }
        std::cout << "Reading..." << path << std::endl;
        std::string line;

        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::vector<double> values;
            std::string value;
            while (std::getline(iss, value, ','))
            {
                values.push_back(std::stod(value));
            }
            points.push_back(Point(values));// Assuming Point constructor can take a vector<double> for N-dimensional points
        }
        file.close();
    }
    // Handle unsupported file types
    else
    {
        std::cout << "File type for row points not supported" << std::endl;
        std::cout << "Supported file types: csv, npy, txt" << std::endl;
        exit(1);
    }

    return points;
}

void KMeansND::save_result()
{
    // Determine the file type based on its extension
    std::string extension = _resultPath.substr(_resultPath.size() - 4);

    // Write data to a CSV file
    if (extension == ".csv")
    {
        std::ofstream file(_resultPath);
        if (!file.is_open())
        {
            std::cout << "Saving error" << std::endl;
            exit(1);
        }
        std::cout << "Writing result..." << std::endl;
        // with coordinates
        if (_with_coordinates)
        {
            // save headers
            file << "cluster_id,distance,";
            for (int i = 0; i < _points.size(); i++)
            {
                file << "x" << i << ",";
            }
            file << std::endl;

            // save data
            for (int i = 0; i < _points.size(); i++)
            {
                file << _points[i].cluster_id << "," << _points[i].distance << ",";
                for (int j = 0; j < _points[i].coords.size(); j++)
                {
                    file << _points[i].coords[j] << ",";
                }
                file << std::endl;
            }
            file.close();
            std::cout << "Wrote " << _points.size() << " points to " << _resultPath << std::endl;
        }
        // without coordinates
        else
        {
            // save headers
            file << "cluster_id,distance" << std::endl;

            // save data
            for (int i = 0; i < _points.size(); i++)
            {
                file << _points[i].cluster_id << "," << _points[i].distance << std::endl;
            }
            file.close();
            std::cout << "Wrote " << _points.size() << " points to " << _resultPath << std::endl;
        }
    }

    else if (extension == ".npy")
    {
        // with coordinates
        if (_with_coordinates)
        {

            // open file
            npy::npy_data file = npy::read_npy<double>(_resultPath);
            std::cout << "Writing result..." << std::endl;
            // save data without headers
            for (int i = 0; i < _centroids.size(); i++)
            {
                file.data[i * file.shape[1] + 0] = _centroids[i].cluster_id;
                file.data[i * file.shape[1] + 1] = _centroids[i].distance;
                for (int j = 0; j < _centroids[i].coords.size(); j++)
                {
                    file.data[i * file.shape[1] + 2 + j] = _centroids[i].coords[j];
                }
            }
            npy::write_npy(_resultPath, file);
            std::cout << "Wrote " << _centroids.size() << " centroids to" << _resultPath << std::endl;
        }
        // without coordinates
        else
        {
            // open file
            npy::npy_data file = npy::read_npy<double>(_resultPath);
            std::cout << "Writing result..." << std::endl;

            // save data without headers
            for (int i = 0; i < _centroids.size(); i++)
            {
                file.data[i * file.shape[1] + 0] = _centroids[i].cluster_id;
                file.data[i * file.shape[1] + 1] = _centroids[i].distance;
            }
            npy::write_npy(_resultPath, file);
            std::cout << "Wrote " << _centroids.size() << " centroids to" << _resultPath << std::endl;
        }
    }
    else if (extension == ".txt")
    {
        // with coordinates
        if (_with_coordinates)
        {
            // open file
            std::ofstream file(_resultPath);
            if (!file.is_open())
            {
                std::cout << "Saving error" << std::endl;
                exit(1);
            }
            std::cout << "Writing result..." << std::endl;
            // save headers
            file << "cluster_id,distance,";
            for (int i = 0; i < _points.size(); i++)
            {
                file << "x" << i << ",";
            }
            file << std::endl;

            // save data
            for (int i = 0; i < _points.size(); i++)
            {
                file << _points[i].cluster_id << "," << _points[i].distance << ",";
                for (int j = 0; j < _points[i].coords.size(); j++)
                {
                    file << _points[i].coords[j] << ",";
                }
                file << std::endl;
            }
            file.close();
            std::cout << "Wrote " << _points.size() << " points to " << _resultPath << std::endl;
        }
        // without coordinates
        else
        {
            // open file
            std::ofstream file(_resultPath);
            if (!file.is_open())
            {
                std::cout << "Saving error" << std::endl;
                exit(1);
            }
            std::cout << "Writing result..." << std::endl;
            // save headers
            file << "cluster_id,distance" << std::endl;

            // save data
            for (int i = 0; i < _points.size(); i++)
            {
                file << _points[i].cluster_id << "," << _points[i].distance << std::endl;
            }
            file.close();
            std::cout << "Wrote " << _points.size() << " points to " << _resultPath << std::endl;
        }
    }
    else
    {
        std::cout << "File type for result not supported" << std::endl;
        std::cout << "Supported file types: csv, npy, txt" << std::endl;
        exit(1);
    }
}

void KMeansND::save_centroids()
{
    // Determine the file type based on its extension
    std::string extension = _resultPath.substr(_resultPath.size() - 4);

    // Write data to a CSV file
    if (extension == ".csv")
    {
        std::ofstream file(_resultPath);
        if (!file.is_open())
        {
            std::cout << "Saving error" << std::endl;
            exit(1);
        }
        std::cout << "Writing result..." << std::endl;
        // always with coordinates
        // save headers
        file << "cluster_id,distance,";
        for (int i = 0; i < _centroids[0].coords.size(); i++)
        {
            file << "x" << i << ",";
        }
        file << std::endl;

        // save data
        for (int i = 0; i < _centroids.size(); i++)
        {
            file << _centroids[i].cluster_id << "," << _centroids[i].distance << ",";
            for (int j = 0; j < _centroids[i].coords.size(); j++)
            {
                file << _centroids[i].coords[j] << ",";
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Wrote " << _centroids.size() << " centroids to " << _resultPath << std::endl;
    }
    else if (extension == ".npy")
    {
        // open file
        npy::npy_data file = npy::read_npy<double>(_resultPath);
        std::cout << "Writing result..." << std::endl;
        // save data
        for (int i = 0; i < _centroids.size(); i++)
        {
            file.data[i * file.shape[1] + 0] = _centroids[i].cluster_id;
            file.data[i * file.shape[1] + 1] = _centroids[i].distance;
            for (int j = 0; j < _centroids[i].coords.size(); j++)
            {
                file.data[i * file.shape[1] + j + 2] = _centroids[i].coords[j];
            }
        }
        npy::write_npy(_resultPath, file);
        std::cout << "Wrote " << _centroids.size() << " centroids to" << _resultPath << std::endl;
    }
    else if (extension == ".txt")
    {
        // open file
        std::ofstream file(_resultPath);
        if (!file.is_open())
        {
            std::cout << "Saving error" << std::endl;
            exit(1);
        }

        std::cout << "Writing result..." << std::endl;
        // save headers
        file << "cluster_id,distance,";
        for (int i = 0; i < _centroids[0].coords.size(); i++)
        {
            file << "x" << i << ",";
        }
        file << std::endl;

        // save data
        for (int i = 0; i < _centroids.size(); i++)
        {
            file << _centroids[i].cluster_id << "," << _centroids[i].distance << ",";
            for (int j = 0; j < _centroids[i].coords.size(); j++)
            {
                file << _centroids[i].coords[j] << ",";
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Wrote " << _centroids.size() << " centroids to " << _resultPath << std::endl;
    }
    else
    {
        std::cout << "File type for clusters not supported" << std::endl;
        std::cout << "Supported file types: csv, npy, txt" << std::endl;
        exit(1);
    }
}

// SOME METHODS FOR DEBUGGING or TESTING or WHATEVER
std::map<int, int> KMeansND::getClustersSize()
{
    std::map<int, int> clusters;
    for (int i = 0; i < _points.size(); i++)
    {
        clusters[_points[i].cluster_id]++;
    }
    return clusters;
}
