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
    double x;       // x value
    double y;       // y value
    double distance;// distance from centroid
    int cluster_id; // id of the cluster to which the point belongs to

    // constructor for row points
    Point(double x, double y) : x(x), y(y), distance(__DBL_MAX__), cluster_id(-1){};
    // constructor for full points
    Point(double x, double y, double distance, int cluster_id) : x(x), y(y), distance(distance), cluster_id(cluster_id){};
    // constructor for centroids
    Point(double x, double y, int cluster_id) : x(x), y(y), distance(0.0), cluster_id(cluster_id){};
    // default constructor
    Point() : x(0.0), y(0.0), distance(0.0), cluster_id(-1){};

    // calculate the distance between two points
    double calcDist(const Point& other) const
    {
        // Euclidean distance
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

// define a function to read data
std::vector<Point> read_data(std::string path);
std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k);

class KMeans
{
protected:
    // store hyperparameters
    int _k;       // store the number of clusters
    int _max_iter;// store the maximum number of iterations

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
    KMeans(int k, int max_iter, std::string pointsPath, std::string centroidsPath, std::string resultPath)
    {
        _k = k;
        _max_iter = max_iter;
        _pointsPath = pointsPath;
        _centroidsPath = centroidsPath;
        _resultPath = resultPath;
        _points = read_data(pointsPath);
        _centroids = initialize_random_centroids(_points, _k);
    }
    KMeans(int k, int max_iter, std::vector<Point> points) : _k(k), _max_iter(max_iter), _points(points), _centroids(initialize_random_centroids(_points, _k)){};
    KMeans(int k, int max_iter) : _k(k), _max_iter(max_iter){};
    void kMeansClustering();
    int assignPointsToClasters();
    void recalculateCentroids();
    // void printClustersSize();
    void save_result_to_csv();
    void save_centroids_to_csv();
    void run();      // run the algorithm and save the result + centroids
    void setPoints(std::vector<Point> points);
    std::vector<Point> getPoints() { return _points; }
};

void KMeans::run()
{
    kMeansClustering();
    save_result_to_csv();
    save_centroids_to_csv();
}

// CLUSTERING MODULE


void KMeans::setPoints(std::vector<Point> points)
{
    _points = points;
    _centroids = initialize_random_centroids(_points, _k);
}
void KMeans::kMeansClustering()
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

int KMeans::assignPointsToClasters()
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

void KMeans::recalculateCentroids()
{
    // reset centroids
    for (int i = 0; i < _centroids.size(); i++)
    {
        _centroids[i].x = 0.0;
        _centroids[i].y = 0.0;
    }
    std::map<int, int> points_per_cluster;// store the number of points in each cluster
    for (int i = 0; i < _points.size(); i++)
    {
        points_per_cluster[_points[i].cluster_id]++;
        _centroids[_points[i].cluster_id].x += _points[i].x;// update x coordinate of the centroid
        _centroids[_points[i].cluster_id].y += _points[i].y;// update y coordinate of the centroid
    }
    // recalculate centroids
    for (int i = 0; i < _centroids.size(); i++)
    {
        _centroids[i].x /= points_per_cluster[i];
        _centroids[i].y /= points_per_cluster[i];
    }
    // check that all centroids are different
    for (int i = 0; i < _centroids.size(); i++)
    {
        for (int j = i + 1; j < _centroids.size(); j++)
        {
            if (_centroids[i].x == _centroids[j].x && _centroids[i].y == _centroids[j].y)
            {
                std::cout << "Centroids are the same" << std::endl;
                exit(1);
            }
        }
    }
}

std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k)
{
    // k is the number of clusters
    // randonly choose k distinct points from the points
    // and ckeck that they are not the same
    std::vector<Point> centroids;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, points.size() - 1);
    std::map<int, bool> used;// store the indexes of used points
    for (int i = 0; i < k; i++)
    {
        int index = dis(gen);
        while (used.find(index) != used.end())// check if the index is used
        {
            index = dis(gen);
        }
        used[index] = true;// mark the index as used
        centroids.push_back(points[index]);
    }
    return centroids;
}


// READING AND WRITING DATA MODULE
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

void KMeans::save_result_to_csv()
{
    // save the result to the csv file
    // in the format:
    // point_index, cluster, distance from the centroid, x_value, y_value
    std::cout << "Saving..." << std::endl;
    std::ofstream file(_resultPath);
    if (!file.is_open())// if the file is not open then error out
    {
        std::cout << "Error saving the file" << std::endl;
        return;
    }
    // save headers
    file << "cluster,distance,x,y" << "\n";

    // save the data to the file

    for (int i = 0; i < _points.size(); i++)// for each point
    {
        std::string line = std::to_string(_points[i].cluster_id) +
                           ',' + std::to_string(_points[i].distance) + ',' +
                           std::to_string(_points[i].x) + ',' + std::to_string(_points[i].y) + "\n";

        file << line;
    }
    std::cout << "Saved to: " << _resultPath << std::endl;// successfully saved
    file.close();
}

void KMeans::save_centroids_to_csv()
{
    // save the centroids to the csv file
    // in the format:
    // cluster, x_value, y_value

    std::ofstream file(_centroidsPath);
    if (!file.is_open())// if the file is not open then error out
    {
        std::cout << "Error saving the centroids" << std::endl;
        return;
    }
    // save headers
    file << "cluster,x,y" << "\n";

    // save the data to the file
    for (int i = 0; i < _centroids.size(); i++)// for each centroid
    {
        file << i << ',' << _centroids[i].x << ',' << _centroids[i].y << '\n';
    }
    file.close();
}