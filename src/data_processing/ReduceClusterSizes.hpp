#pragma once
#include "../clustering_core/KmeansND.hpp"
#include "Clusters.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::vector<Point> combinePoints(const std::vector<Point>& points, const std::vector<int>& cluster_ids, const std::vector<Point>& cluster_centers)
{
    std::vector<Point> combined_points(points.size());
    for (size_t i = 0; i < points.size(); ++i)
    {
        combined_points[i] = points[i];
        combined_points[i].cluster_id = cluster_ids[i];
        combined_points[i].distance = combined_points[i].calcDist(cluster_centers[cluster_ids[i]]);
    }
    return combined_points;
}

std::vector<Point> readCentroids_from_csv(const std::string& filename)
{
    std::vector<Point> centroids;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return centroids;
    }

    std::string line;
    // skip first line
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string value;
        std::vector<double> coordinates;
        int cluster_id;

        // read cluster_id
        std::getline(iss, value, ',');
        cluster_id = std::stoi(value);

        // read coordinates
        while (std::getline(iss, value, ','))
        {
            coordinates.push_back(std::stod(value));
        }
        centroids.push_back(Point(coordinates, cluster_id, 0));
    }
    return centroids;
}

std::vector<int> readClusterIds_csv(const std::string& filename)
{
    // data in the file is in the following format:
    // 1. cluster_id
    // 2. cluster_id
    // ...
    std::vector<int> cluster_ids;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return cluster_ids;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string value;
        int cluster_id;
        std::getline(iss, value, ',');
        cluster_id = std::stoi(value);
        cluster_ids.push_back(cluster_id);
    }
    return cluster_ids;
}

std::vector<Cluster> ReduceClusterSize(const std::string& pathToClusters, const std::string& pathToCentroids, const std::string& pathEmbeddings)
{
    std::vector<Point> centroids = readCentroids_from_csv(pathToCentroids);// shape: (num_clusters, num_features)
    std::vector<int> cluster_id = readClusterIds_csv(pathToClusters);      // shape: (num_points,)
    std::vector<Point> rowPoints = read_data(pathEmbeddings);              // shape: (num_points, num_features)

    std::vector<Point> combined_points = combinePoints(rowPoints, cluster_id, centroids);
    std::vector<Cluster> clusters;
    std::vector<std::vector<Point>> clusters_points = returnClusters(combined_points, centroids);
    for (size_t i = 0; i < clusters_points.size(); ++i)
    {
        Cluster c(i, clusters_points[i]);
        clusters.push_back(c);
    }
    return clusters;
}