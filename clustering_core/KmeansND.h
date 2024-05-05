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


struct Point {
    std::vector<double> coords;
    double distance;// distance from centroid
    int cluster_id; // id of the cluster to which the point belongs to

    // constructor for row points
    Point(const std::vector<double>& coords) : coords(coords), distance(INT_MAX), cluster_id(-1){};

    // constructor for centroids
    Point(const std::vector<double>& coords, int cluster_id) : coords(coords), distance(0), cluster_id(cluster_id){};

    // default constructor
    Point() : distance(INT_MAX), cluster_id(-1), coords({}){};

    // constructor from initializer list (test case)
    Point(std::initializer_list<double> list) : coords(list) {}

    // calculate the euclidian distance between two points

    double calcDist(const Point& other) const
    {
        double sum = 0;
        for (int i = 0; i < coords.size(); i++)
        {
            sum += pow(coords[i] - other.coords[i], 2);
        }
        return sqrt(sum);
    }

    // destructor
    ~Point() = default;
};

std::vector<Point> read_data(std::string path);
std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k);

class KMeansND
{
protected:
    // store hyperparameters
    int _k;       // store the number of clusters
    int _max_iter;// store the maximum number of iterations

    bool _with_coordinates;// if true, then save the coordinates of points in output file
    // default value is false (for saving memory)

    // store centroids
    // i-th element store the coordinates of i-th centroid
    std::vector<Point> _centroids;

    // store file paths
    std::string _pointsPath;   // store the path of the file with row points
    std::string _centroidsPath;// store the path of the file to write centroids
    std::string _resultPath;   // store the path of the file to write result

    // store points
    std::vector<Point> _points;// store all points

public:
    // constructor
    KMeansND(int k, int max_iter, std::string pointsPath, std::string centroidsPath, std::string resultPath)
    {
        _k = k;
        _max_iter = max_iter;
        _pointsPath = pointsPath;
        _centroidsPath = centroidsPath;
        _resultPath = resultPath;
        _points = read_data(_pointsPath);
        _centroids = initialize_random_centroids(_points, _k);
        _with_coordinates = false;
    }

    KMeansND(int k, int max_iter, std::vector<Point> points)
    {
        _k = k;
        _max_iter = max_iter;
        _points = points;
        _centroids = initialize_random_centroids(_points, _k);
        _with_coordinates = false;
    }

    KMeansND(int k, int max_iter) : _k(k), _max_iter(max_iter), _with_coordinates(false){};
    // default constructor
    ~KMeansND() = default;
    // copy constructor
    KMeansND(const KMeansND& other) : _k(other._k), _max_iter(other._max_iter), _points(other._points), _centroids(other._centroids), _with_coordinates(other._with_coordinates), _pointsPath(other._pointsPath), _centroidsPath(other._centroidsPath), _resultPath(other._resultPath){};

    void kMeansClustering();
    int assignPointsToClasters();
    void recalculateCentroids();
    // void printClustersSize();
    void save_result();
    void save_centroids();
    void run(bool show_time);// run the algorithm and save the result + centroids
    void setPoints(std::vector<Point> points);
    std::vector<Point> getPoints() { return _points; }
    std::vector<Point> getCentroids() { return _centroids; }
    void setCentroids(std::vector<Point> centroids) { _centroids = centroids; }
    void setMaxIter(int max_iter) { _max_iter = max_iter; }
    void setPointsPath(std::string pointsPath) { _pointsPath = pointsPath; }
    void setCentroidsPath(std::string centroidsPath) { _centroidsPath = centroidsPath; }
    void setResultPath(std::string resultPath) { _resultPath = resultPath; }
    void setWithCoordinates(bool with_coordinates) { _with_coordinates = with_coordinates; }
    void setK(int k) { _k = k; }
    int getK() { return _k; }
    std::map<int, int> getClustersSize();
};
void KMeansND::run(bool show_time = false)
{
    if (show_time)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        kMeansClustering();
        save_result();
        save_centroids();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    }
    else
    {
        kMeansClustering();
        save_result();
        save_centroids();
    }
}

void KMeansND::setPoints(std::vector<Point> points)
{
    _points = points;
    _centroids = initialize_random_centroids(_points, _k);
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
