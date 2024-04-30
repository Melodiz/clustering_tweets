#include <algorithm>// for sorting
#include <chrono>   // for time measurement
#include <cmath>    // for pow and other math functions
#include <fstream>
#include <iostream>
#include <map>
#include <random>// for randomly initializing centroids
#include <string>
#include <utility>
#include <vector>

// define all functions and data structures
struct Point;
std::vector<Point> read_data(const std::string& filePath);
std::vector<Point> kMeansClustering(std::vector<Point>& points, int epochs, int k);
std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k);
int assignPointsToClasters(std::vector<Point>& points, const std::vector<Point>& centroids);
void recalculateCentroids(std::vector<Point>& points, std::vector<Point>& centroids);
void printClustersSize(const std::vector<Point>& points, const std::vector<Point>& centroids);
void save_result_to_csv(const std::vector<Point>& points, const std::string& filename);
void save_centroids_to_csv(const std::vector<Point>& centroids, const std::string& filename);


// implementation of each point
struct Point {
    std::vector<double> coords;// coordinates of the point
    int cluster;               // cluster to which the point is assigned
    double distance;           // distance to the centroid of the assigned cluster

    // constructor
    Point(std::vector<double> coords, int cluster, double distance) : coords(coords), cluster(cluster), distance(distance){};

    // default constructor
    Point()
    {
        // since we don't know the coordinates of the point, we set them to 0
        // standart model for embeddings is 384 dimensional "all-minilm"
        coords = std::vector<double>();// zere vector in 384 dimensions
        cluster = -1;                  // unassigned
        distance = __DBL_MAX__;        // infinity
    }
    Point(const std::vector<double>& coords) : coords(coords), cluster(-1), distance(__DBL_MAX__){};

    // calculate the distance between two points
    double dist(Point other)
    {
        double sum = 0;
        for (int i = 0; i < coords.size(); i++)
        {
            sum += pow((coords[i] - other.coords[i]), 2);
        }
        return std::sqrt(sum);
    }
};

std::vector<Point> read_data(const std::string& filePath)
{
    // file contains x and y coordinates
    std::vector<Point> points = {};
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return points;
    }
    std::cout << "Reading... <" << filePath << ">\n"
              << std::endl;
    std::string line;
    std::getline(file, line);// skip the header line
    while (std::getline(file, line))
    {
        std::vector<double> coords = {};
        double x = std::stold(line.substr(0, line.find(',')));
        double y = std::stold(line.substr(line.find(',') + 1));
        coords.push_back(x);
        coords.push_back(y);
        points.push_back(Point(coords));
    }
    file.close();
    return points;
}
std::vector<Point> kMeansClustering(std::vector<Point>& points, int epochs, int k)
{
    // points is all points in the dataset
    // k is the number of clusters
    // epochs is the number of iterations

    // initialize the centroids for first time
    std::vector<Point> centroids = initialize_random_centroids(points, k);

    std::cout << "Initializing..." << std::endl;
    int changed = 0;// number of changed points
    for (int i = 0; i < epochs; i++)
    {
        std::cout << "Iteration " << i + 1 << "..." << std::endl;
        // recalculate the centroids
        changed = assignPointsToClasters(points, centroids);
        // assign each point to the closest centroid
        recalculateCentroids(points, centroids);
        std::cout << "Points changed: " << changed << std::endl;
        // printClustersSize(points, centroids);// print the number of points in each cluster
        if (changed == 0)// if there are no changed points
            break;
    }
    std::cout << "Clusterization done successfully" << std::endl;
    // finally assign each point to the closest centroid
    assignPointsToClasters(points, centroids);
    return centroids;// return the centroids
}

std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k)
{
    // k is the number of clusters
    std::vector<Point> centroids = {};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, points.size() - 1);
    for (int i = 0; i < k; i++)
    {
        centroids.push_back(points[dis(gen)]);
    }
    return centroids;
}


int assignPointsToClasters(std::vector<Point>& points, const std::vector<Point>& centroids)
{
    // assign each point to the closest centroid
    int changed = 0;
    for (int i = 0; i < points.size(); i++)
    {
        double minDistance = __DBL_MAX__;
        int minIndex = -1;
        for (int j = 0; j < centroids.size(); j++)
        {
            double distance = points[i].dist(centroids[j]);
            if (distance < minDistance)
            {
                minDistance = distance;
                minIndex = j;
            }
        }
        if (points[i].cluster != minIndex)
        {
            points[i].cluster = minIndex;
            changed++;
        }
    }
    return changed;// return the number of changed points due iteration
}

std::map<int, std::pair<std::vector<double>, std::vector<double>>> clMap;

void recalculateCentroids(std::vector<Point>& points, std::vector<Point>& centroids)
{
    // recalculate the centroids

    std::map<int, std::pair<std::vector<double>, std::vector<double>>> clMap;

    // for each cluster calculate the sum of all points in the cluster
    for (size_t i = 0; i < points.size(); i++)
    {
        clMap[points[i].cluster].first.push_back(points[i].coords[0]);
        clMap[points[i].cluster].second.push_back(points[i].coords[1]);
    }

    // for each cluster calculate the mean of all points in the cluster
    for (size_t i = 0; i < centroids.size(); i++)
    {
        Point newCentroid;      // initialize new centroid
        newCentroid.cluster = i;// set the cluster number to the new centroid
        // calculate the mean of all points in the cluster and set it to the new centroid
        newCentroid.coords.push_back(std::accumulate(clMap[i].first.begin(), clMap[i].first.end(), 0.0) / clMap[i].first.size());
        newCentroid.coords.push_back(std::accumulate(clMap[i].second.begin(), clMap[i].second.end(), 0.0) / clMap[i].second.size());
        centroids[i] = newCentroid;// set the new centroid to the centroids
    }
}

void save_centroids_to_csv(const std::vector<Point>& centroids, const std::string& filename)
{
    std::cout << "Saving centroids..." << std::endl;
    std::ofstream file(filename);
    if (!file.is_open())// if the file is not open then error out
    {
        std::cout << "Error saving the file" << std::endl;
        return;
    }
    // save headers
    file << "cluster,x,y\n";
    // save the data to the file
    for (int i = 0; i < centroids.size(); i++)// for each point
    {
        file << centroids[i].cluster << ',' << centroids[i].coords[0] << ',' << centroids[i].coords[1] << '\n';
    }
    std::cout << "Centroinds saved to: " << filename << std::endl;// successfully saved
    file.close();
}

void save_result_to_csv(const std::vector<Point>& points, const std::string& filename)
{
    // save the result to the csv file
    // in the format:
    // point_index, cluster, distance from the centroid, x_value, y_value
    std::cout << "Saving..." << std::endl;
    std::ofstream file(filename);
    if (!file.is_open())// if the file is not open then error out
    {
        std::cout << "Error saving the file" << std::endl;
        return;
    }
    // save headers
    file << "id,cluster,distance,x,y" << "\n";

    // save the data to the file
    for (int i = 0; i < points.size(); i++)// for each point
    {
        file << i << ',' << std::to_string(points[i].cluster) << ',' << points[i].distance << points[i].coords[0] << ',' << points[i].coords[1] << '\n';
    }
    std::cout << "Saved to: " << filename << std::endl;// successfully saved
    file.close();
}
// ________________________________________________________________________________________________