#include "include/npy.hpp"
#include "modules/clusterTools.hpp"
#include "modules/kMeansLogic.hpp"
#include "modules/readData.hpp"
#include "modules/writeData.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <utility>
#include <vector>


class KMeansND
{
protected:
    int _k;
    int _max_iter;
    bool _with_coordinates;

    std::vector<Point> _centroids;

    std::string _pointsPath;
    std::string _centroidsPath;
    std::string _resultPath;

    std::vector<Point> _points;

public:
    KMeansND(int k, int max_iter, std::string pointsPath, std::string centroidsPath, std::string resultPath)
    {
        _k = k;
        _max_iter = max_iter;
        _pointsPath = pointsPath;
        _centroidsPath = centroidsPath;
        _resultPath = resultPath;
        _with_coordinates = false;
        _points = read_data(_pointsPath);
        _centroids = initialize_random_centroids(_points, _k);
    }
    KMeansND(int k, int max_iter, std::vector<Point> points) : _k(k), _max_iter(max_iter), _points(points), _centroids(initialize_random_centroids(points, k)){};

    KMeansND(int k, int max_iter) : _k(k), _max_iter(max_iter){};

    ~KMeansND() = default;

    void Cluster(bool showStatus);
    void save();

    void setK(int k) { _k = k; };
    void setPoints(std::vector<Point> points);
    void setCentroids(std::vector<Point> centroids) { _centroids = centroids; };
    void setMaxIter(int max_iter) { _max_iter = max_iter; };
    void setPointsPath(std::string pointsPath) { _pointsPath = pointsPath; };
    void setCentroidsPath(std::string centroidsPath) { _centroidsPath = centroidsPath; };
    void setResultPath(std::string resultPath) { _resultPath = resultPath; };
    void setWithCoordinates(bool with_coordinates) { _with_coordinates = with_coordinates; };

    std::vector<Point> getPoints() { return _points; };
    std::vector<Point> getCentroids() { return _centroids; };
    int getK() { return _k; };
    std::map<int, int> getClustersSize() { return returnClustersSize(_points); }
};

void KMeansND::Cluster(bool showStatus = false)// run clustering algorithm
{
    int pointsChanged = assignPointsToCentroids(_points, _centroids);
    int iter = 0;
    while (pointsChanged && iter < _max_iter)
    {
        // debugShowFullData(_points, _centroids); // uncomment for debugging
        recalculateCentroids(_points, _centroids);
        pointsChanged = assignPointsToCentroids(_points, _centroids);
        iter++;
        if (showStatus) { iterationStatus(iter, pointsChanged); }
    }
    if (showStatus) { std::cout << "Clustering finished" << std::endl; }
}

void KMeansND::save()
{
    save_result(_resultPath, _points, _centroids, _with_coordinates);
    save_centroids(_centroidsPath, _centroids);
}

void KMeansND::setPoints(std::vector<Point> points)
{
    _points = points;
    _centroids = initialize_random_centroids(points, _k);
}
