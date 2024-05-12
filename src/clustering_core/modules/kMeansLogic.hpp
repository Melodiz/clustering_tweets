#pragma once
#include "structPoint.hpp" // Point structure definition
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <random> // for randomly generated centroids

std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k);
int assignPointsToCentroids(std::vector<Point>& _points, std::vector<Point>& _centroids);
void recalculateCentroids(std::vector<Point>& _points, std::vector<Point>& _centroids);

int assignPointsToCentroids(std::vector<Point>& _points, std::vector<Point>& _centroids)
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


void recalculateCentroids(std::vector<Point>& _points, std::vector<Point>& _centroids)
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
