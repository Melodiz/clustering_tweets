// Clusters.hpp
#pragma once
#include "../clustering_core/modules/structPoint.hpp"
#include "modules/SortingClusters.hpp"
#include "modules/ClusterRelevantInfo.hpp"
#include <string>
#include <vector>

class Cluster;

typedef std::vector<Cluster> Clusters;

class Cluster
{
public:
    Cluster() : cluster_id(-1), num_points(0) {}
    Cluster(int id) : cluster_id(id), num_points(0) {}
    Cluster(int id, const Point& center) : cluster_id(id), center(center), num_points(0) {}
    Cluster(int id, const std::vector<Point>& points) : cluster_id(id), points(points), num_points(points.size()) {}
    Cluster(int id, const Point& center, const std::vector<Point>& points) : cluster_id(id), center(center), points(points), num_points(points.size()) {}
    Cluster(int id, const Point& center, const std::vector<Point>& points, int num_points) : cluster_id(id), center(center), points(points), num_points(num_points) {}

    int getClusterId() const { return cluster_id; }
    int getNumPoints() const { return num_points; }
    const Point& getCenter() const { return center; }
    const std::vector<Point>& getPoints() const { return points; }

    void sort() { sortPointsByDistance(center, points); }

    std::vector<Point> getNeighbors(int k) const { return ::getNeighbors(center, points, k); }

protected:
    int cluster_id;
    Point center;
    std::vector<Point> points;
    int num_points;
};